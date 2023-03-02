#include "../include/nested_loop_join_executor.h"
#include "../include/seq_scan_executor.h"
#include <iostream>

using std::cout;
using std::endl;

NestedLoopJoinExecutor::NestedLoopJoinExecutor(
    AbstractExecutor *left_child_executor,
    AbstractExecutor *right_child_executor, const std::string join_key)
    : left_(left_child_executor),
      right_(right_child_executor),
      join_key_(join_key){};

void NestedLoopJoinExecutor::Init() {
  ((SeqScanExecutor *) left_)->Init();
}

bool NestedLoopJoinExecutor::Next(Tuple *tuple) { 

  if(!nestedTuple.empty()){
    const Tuple &curr_tuple = nestedTuple.front();
    *tuple = Tuple(curr_tuple);
    nestedTuple.erase(nestedTuple.begin());
    
    return true;
  }
  else{
    Tuple seqTuple1;
    while (((SeqScanExecutor *) left_)->Next(&seqTuple1)) {
    
      ((SeqScanExecutor *) right_)->Init();
      Tuple seqTuple2;
      while (((SeqScanExecutor *) right_)->Next(&seqTuple2)){

        if(join_key_ == "val1" && seqTuple1.val1 == seqTuple2.val1){
          nestedTuple.push_back(seqTuple1);
        }

        if(join_key_ == "val2" && seqTuple1.val2 == seqTuple2.val2){
          nestedTuple.push_back(seqTuple1);
        }
      }

      if(!nestedTuple.empty()){
        const Tuple &curr_tuple = nestedTuple.front();
        *tuple = Tuple(curr_tuple);
        nestedTuple.erase(nestedTuple.begin());
        
        return true;
      }
    }
  }
  
  return false; 
}
