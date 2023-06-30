/* 
    Name: Eric Wu
    Professor: Ms.Tiziana Ligorio
    Course: CS235
    Date Due: 02/10/2023
    Description: This program adds sorting into the cardshop class
*/

#ifndef CARD_SHOP_HPP_
#define CARD_SHOP_HPP_
#include "DoublyLinkedList.hpp"
#include "YGOCard.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Node.hpp"


class CardShop : public DoublyLinkedList<YGOCard *>
{
public:
  CardShop() = default; //default constructor
  ~CardShop();          //destructor calls clear

  /**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
  CardShop(std::string input_file_name); //parameterized constructor

  //@post: displays information of all cards in the shop, one per line
  void display();

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
  void displayName(int startRange, int endRange);

  //@post: removes all cards from the shop
  void clear();                               

  //@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
  bool operator==(const CardShop &rhs) const; 

/** Sorts the items in an array into ascending order or descending order depending on Comp value
@pre None.
@post cards attacks/defenses are sorterd in ascending or descending order depending on comp and key
@param comp that telsl if it'll descend or ascend, and key lets us know if we should be comparing attack or defense
*/
  template<typename Comparator>
  int bubbleSort(const Comparator &comp, const std::string &key);

/** Sorts the items in an array into ascending order or descending order depending on Comp value
@pre None.
@post cards attacks/defenses are sorterd in ascending or descending order depending on comp and key
@param comp that telsl if it'll descend or ascend, and key lets us know if we should be comparing attack or defense
z*/
  template<typename Comparator>
  int insertionSort(const Comparator &comp, const std::string &key);

/*
Will not be implemented
*/
  template<typename Comparator>
  int mergeSort(Comparator comp, std::string key);

/** Sorts the items in an array into ascending order or descending order depending on Comp value
@pre None.
@post cards attacks/defenses are sorterd in ascending or descending order depending on comp and key
@param comp that telsl if it'll descend or ascend, and key lets us know if we should be comparing attack or defense
*/
  template<typename Comparator>
  int quickSort(const Comparator &comp, const std::string &key);
  
//helper function for quickSort
//param i = starting index, j = ending index
  template<typename Comparator>
  void quickSort(const Comparator &comp, const std::string &key, int i, int j, int &times_sorted);

//partition for quickSort
//param i = starting indedx, j = ending index
  template<typename Comparator>
  int partition(const Comparator &comp, const std::string &key, int i, int j, int &times_sorted);  
};

#endif
