//
//  main.cpp
//  ContinousMedian
//
//  Created by adeeb mohammed on 23/03/20.
//  Copyright © 2020 adeeb mohammed. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdlib>

// Do not edit the class below except for
// the insert method. Feel free to add new
// properties and methods to the class.
/*
 the basic idea of the program is that
 we have to find the average of root node of minheap
 or root node of max heap
 or rebalance the tree for getting the median at a given point of time
 
 heap child index left =  2i+1
                right = 2i+2
 root node = (currentIdx - 1)  / 2
 */

class Heap{
private:
    std::vector<int> heap;
    int type = 0;
public:
    
    Heap(int type){
        this->type = type;
    }
    
    int getPeek(){
        return this->heap.at(0);
    }
    
    void insert(int value){
        heap.push_back(value);
        shiftUp(getLength()-1);
    }

    
    void remove(){
        swap(0,getLength()-1);
        heap.pop_back();
        shiftDown(0);
    }
    
    int getLength(){
        return (int)this->heap.size();
    }
    
    void printHeap(){
        for(auto num : heap){
            std::cout<< num << " ";
        }
    }
    
    
private:
    // basic operations of a heap
    void shiftUp(int currentIdx){
        switch (this->type) {
            case 0:
                shiftUpMin(currentIdx);
                break;
            case 1:
                shiftUpMax(currentIdx);
                break;
            default:
                break;
        }
    }
    
    void shiftDown(int currentIdx){
        switch (this->type) {
            case 0:
                shiftDownMin(currentIdx);
                break;
            case 1:
                shiftDownMax(currentIdx);
                break;
            default:
                break;
        }
    }
    
    void shiftUpMax(int currentIdx){
        int parentIdx = (currentIdx-1)/2;
        while(parentIdx >= 0 && this->heap.at(currentIdx) > this->heap.at(parentIdx)){
            swap(parentIdx, currentIdx);
            currentIdx = parentIdx;
            parentIdx  = (currentIdx-1)/2;
        }
    }
    
    void shiftUpMin(int currentIdx){
        int parentIdx = (currentIdx-1)/2;
        while(parentIdx >= 0 && this->heap.at(currentIdx) < this->heap.at(parentIdx)){
            swap(parentIdx, currentIdx);
            currentIdx = parentIdx;
            parentIdx  = (currentIdx-1)/2;
        }
    }
    
    
    void shiftDownMin(int currentIdx){
        int childOneIdx = (currentIdx*2)+1;
        while(childOneIdx < this->getLength()){
            int childTwoIdx = childOneIdx+1;
            int idxtoSwap = childOneIdx;
            if (childTwoIdx < this->getLength() &&
                this->heap.at(childTwoIdx) < this->heap.at(childOneIdx)) {
                idxtoSwap = childTwoIdx;
            }
            if (this->heap.at(idxtoSwap) < this->heap.at(currentIdx)) {
                this->swap(currentIdx, idxtoSwap);
                currentIdx = idxtoSwap;
                childOneIdx = (currentIdx*2) + 1;
            }else{
                return;
            }
        }
    }
    
    void shiftDownMax(int currentIdx){
        int childOneIdx = (currentIdx*2)+1;
        while(childOneIdx < this->getLength()){
            int childTwoIdx = childOneIdx+1;
            int idxtoSwap = childOneIdx;
            if (childTwoIdx < this->getLength() &&
                this->heap.at(childTwoIdx) > this->heap.at(childOneIdx)) {
                idxtoSwap = childTwoIdx;
            }
            if (this->heap.at(idxtoSwap) > this->heap.at(currentIdx)) {
                this->swap(currentIdx, idxtoSwap);
                currentIdx = idxtoSwap;
                childOneIdx = (currentIdx*2) + 1;
            }else{
                return;
            }
        }
    }

    void swap(int fromIdx, int toIdx){
        int temp = this->heap.at(fromIdx);
        this->heap.at(fromIdx) = this->heap.at(toIdx);
        this->heap.at(toIdx) = temp;
    }
    
};

class ContinuousMedianHandler {
private:
    Heap *pMinHeap = new Heap(0); // heap for storing the larger numbers
    Heap *pMaxHeap = new Heap(1); // heap for storing the lesser numbers
    
public:
  double median;
  
  void insert(int number) {
      if(!pMaxHeap->getLength() || pMaxHeap->getPeek() > number){
          pMaxHeap->insert(number);
      }else{
          pMinHeap->insert(number);
      }
      rebalanceHeaps();
      updateMedian();
  }

double getMedian() { return median; }
~ContinuousMedianHandler(){
    delete pMinHeap;
    delete pMaxHeap;
}

private:
    
    void rebalanceHeaps(){
        if(pMaxHeap->getLength() - pMinHeap->getLength() == 2){
            pMinHeap->insert(pMaxHeap->getPeek());
            pMaxHeap->remove();
        }else if(pMinHeap->getLength() - pMaxHeap->getLength() == 2){
            pMaxHeap->insert(pMinHeap->getPeek());
            pMinHeap->remove();
        }
        
        //std::cout << "----------------------" << std::endl;
        //std::cout << "Min Heap ";pMinHeap->printHeap(); std::cout << std::endl;
        //std::cout << "Max Heap ";pMaxHeap->printHeap(); std::cout << std::endl;
        //std::cout << "----------------------"<< std::endl;
    }
    
    void updateMedian(){
        //std::cout << "Entered here" << std::endl;
        if(pMaxHeap->getLength() == pMinHeap->getLength()){
            this->median = (double)(pMaxHeap->getPeek()+pMinHeap->getPeek())/2;
        } else if (pMaxHeap->getLength() > pMinHeap->getLength()){
            this->median = (double)pMaxHeap->getPeek();
        }else{
            this->median = (double)pMinHeap->getPeek();
        }
        //std::cout << "Exit Here" << std::endl;
    }
    
};

int main(int argc, const char * argv[]) {
    std::cout << "Program for continous median!"<<std::endl;
    ContinuousMedianHandler median;
    median.insert(5);
    median.insert(10);
    std::cout << "Median " << median.getMedian() << std::endl;
    median.insert(100);
    median.insert(200);
    std::cout << "Median " << median.getMedian() << std::endl;
    median.insert(6);
    median.insert(13);
    std::cout << "Median " << median.getMedian() << std::endl;
    median.insert(14);
    median.insert(50);
    std::cout << "Median " << median.getMedian() << std::endl;
    
    return 0;
}
