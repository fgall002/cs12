#include <iostream>
#include <cstdlib>
#include <vector>
#include "Deck.h"
using namespace std;


void merge(vector<Card> &x, unsigned begin, unsigned mid, unsigned end) {
    
   unsigned int mergedSize = end - begin + 1;       // Size of merged partition
   vector<Card> mergerdCards(mergedSize);    // Temporary array for merged numbers
   unsigned int mergePos = 0;                 // Position to insert merged number
   unsigned int leftPos = 0;                  // Position of elements in left partition
   unsigned int rightPos = 0;                 // Position of elements in right partition
   
   leftPos = begin;                      // Initialize left partition position
   rightPos = mid + 1;                 // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= mid && rightPos <= end) {
      if (x.at(leftPos).getSuit() == (x.at(rightPos)).getSuit()) {
         if ((x.at(leftPos)).getRank() < (x.at(rightPos)).getRank()){
            mergerdCards.at(mergePos) = (x.at(leftPos));
            ++leftPos;
         }
         else {
            mergerdCards.at(mergePos) = (x.at(rightPos));
            ++rightPos;
         }
      }
      else if (x.at(leftPos).getSuit() < x.at(rightPos).getSuit()) {
         mergerdCards.at(mergePos) = (x.at(leftPos));
         ++leftPos;
      }
      else if (x.at(leftPos).getSuit()  > x.at(rightPos).getSuit()) {
         mergerdCards.at(mergePos) = (x.at(rightPos));
         ++rightPos;
         
      }
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= mid) {
      mergerdCards.at(mergePos) = (x.at(leftPos));
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= end) {
      mergerdCards.at(mergePos) = (x.at(rightPos));
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   //x.clear();
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      //[i + mergePos] = mergedNumbers[mergePos];
      x.at(begin + mergePos) = mergerdCards.at(mergePos);
   }
    
}


void fillHand(vector<Card> &hand, Deck &d, unsigned handSize) {
   hand.resize(handSize);
   for (unsigned i = 0; i < hand.size(); ++i) {
      hand.at(i) = d.dealCard();
   }
}

void mergeSort(vector<Card> &v, unsigned begin, unsigned end) {
    if (begin < end) {
          
       int mid = (begin + end) / 2;
       
       mergeSort(v, begin, mid);
       
       mergeSort(v, mid + 1, end);
       
       merge(v, begin, mid, end);
    }
    
}
    
void sortBySuit(vector<Card> &v) {
    if (!v.empty()) {
          
       int start = 0;
       int end = v.size() - 1; 
       mergeSort(v, start, end);
    }
    
}
    



//This is the function you implemented for PROGRAM 3
ostream & operator<<(ostream & out, const vector<Card> & hand);

int main() {
   vector<Card> hand;
   Deck deck;
   int handSize;
   int seed;
   cout << "Enter seed value: ";
   cin >> seed;
   cout << endl;
   cout << "Enter hand size: ";
   cin >> handSize;
   cout << endl;

   srand(seed);
   deck.shuffleDeck();
   fillHand(hand, deck, handSize);
   cout << hand << endl;
   sortBySuit(hand);
   cout << hand << endl;
   return 0;
}

ostream & operator<<(ostream & out, const vector<Card> &hand) {
   if (hand.size() == 0) {
        return out;
    }
        for (unsigned int i = 0; i < hand.size() - 1; i++) {
            
            out << hand.at(i) << ", ";
            
        }
            out << hand.at(hand.size() - 1);

    return out;
}
