#include "../include/hash_join_executor.h"
#include "../include/seq_scan_executor.h"

using std::cout;
using std::endl;

HashJoinExecutor::HashJoinExecutor(AbstractExecutor *left_child_executor,
                                   AbstractExecutor *right_child_executor,
                                   SimpleHashFunction *hash_fn)
    : left_(left_child_executor),
      right_(right_child_executor),
      hash_fn_(hash_fn) {}

void HashJoinExecutor::Init(){
  ((SeqScanExecutor *) left_)->Init();
  ((SeqScanExecutor *) right_)->Init();
  ht.clearHashTable();
  Tuple tuple;
  while(((SeqScanExecutor *) left_)->Next(&tuple)){
    ht.Insert(hash_fn_->GetHash(tuple), tuple);
  }
};

bool HashJoinExecutor::Next(Tuple *tuple) {
  
  if(!hashTuple.empty()){
    const Tuple &curr_tuple = hashTuple.front();
    *tuple = Tuple(curr_tuple);
    hashTuple.erase(hashTuple.begin());
   
    return true;
  }  
  
  if(hashTuple.empty()){
    Tuple seqTuple;
    while(((SeqScanExecutor *) right_)->Next(&seqTuple)){
    ht.GetValue(hash_fn_->GetHash(seqTuple), &hashTuple);
      if(!hashTuple.empty()){
        const Tuple &curr_tuple = hashTuple.front();
       *tuple = Tuple(curr_tuple);
        hashTuple.erase(hashTuple.begin());
        
        return true;
      }  
    }
  }
  
  return false; 
}
