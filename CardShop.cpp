
/* 
    Name: Eric Wu
    Professor: Ms.Tiziana Ligorio
    Course: CS235
    Date Due: 02/10/2023
    Description: This program adds sorting into the cardshop class
*/

#include "CardShop.hpp"
#include "Node.hpp"
#include <iostream>
#include <fstream>
#include <sstream>


/**
  @pre  : the input file is in csv format: "name,type,level_rank,race,attribute,atk,def"
  @param: the name of the input file
  @post:  Reads the input file and adds pointers to YGOCard objects 
          instantiated with the information read from the file. 
    */
CardShop::CardShop(std::string input_file_name) 
{
  std::ifstream fin(input_file_name);
  if (fin.fail())
  {
    std::cerr << "File cannot be opened for reading. \n";
    exit(1); // exit if failed to open the file
  }
  //we don't use the first line
  std::string ignore;
  getline(fin, ignore);

  //the columns of the csv associated with the data members
  std::string name, type, race, attribute;
  int level_rank, atk, def;

  std::string temp_string;
  int temp_int;
  int item_counter = 0;
  while (getline(fin, temp_string, ','))
  {
    name = temp_string;

    getline(fin, type, ',');
  
    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    level_rank = temp_int;

    getline(fin, race, ',');

    getline(fin, attribute, ',');

    getline(fin, temp_string, ',');
    std::istringstream(temp_string) >> temp_int;
    atk = temp_int;

    getline(fin, temp_string);
    std::istringstream(temp_string) >> temp_int;
    def = temp_int;

    //create new card
    YGOCard *card_ptr = new YGOCard(name, type, level_rank, race, attribute, atk, def);

    //add to linked list and increment counter
    insert(item_counter++, card_ptr);
  }
}

//@post: removes all cards from the shop
//Deallocate and delete items
void CardShop::clear()
{
  for (int i = 0; i < item_count_; i++)
  {
    YGOCard *ptr = getItem(i);
    delete ptr;
    ptr = nullptr;
  }
  DoublyLinkedList::clear();
}

//destructor
CardShop::~CardShop()
{
  clear();
}

//@post: displays information of all cards in the shop, one per line
void CardShop::display()
{
  for (int i = 0; i < item_count_; i++)
  {
    getItem(i)->display();
  }
}

  //@param: the index of the first card to be displayed
  //@param: the index of the last card to be displayed
  //@post: displays the names of all cards in the shop with startRange and endRange, 
  //       inclusive, one per line
void CardShop::displayName(int startRange, int endRange)
{
  for (int i = startRange; i <= endRange; i++)
  {
    getItem(i)->displayName();
    if (i != endRange)
    {
      std::cout << ", ";
    }
    else
    {
      std::cout << std::endl;
    }
  }
}


//@return:  true if all the cards in rhs are equal to the cards in the shop, false otherwise
bool CardShop::operator==(const CardShop &rhs) const
{
  if (getLength() != rhs.getLength())
  {
    return false;
  }
  for (int i = 0; i < getLength(); i++)
  {
    if (*(getPointerTo(i)->getItem()) == *(rhs.getPointerTo(i)->getItem()))
    {
    }
    else
    {
      return false;
    }
  }
  return true;
}

template<typename Comparator>
int CardShop::bubbleSort(const Comparator &comp, const std::string &key)
{
  bool sorted = false;
  int times_sorted = 0;
  int pass = 1;
  while(!sorted && (pass < item_count_))
  {
    sorted = true;
    for(int i = 0; i < item_count_ - pass; i++)
    {
      int j = i + 1;
      if(key == "atk")//checks if atk or def should be sorted
      {
        if(comp(getPointerTo(j) -> getItem() -> getAtk(), getPointerTo(i) -> getItem() -> getAtk()))
        {
          swap(i, j);
          times_sorted++;
          sorted = false;
        } 
      }
      else if(key == "def")
      {
        if(comp(getPointerTo(j) -> getItem() -> getDef(), getPointerTo(i) -> getItem() -> getDef()))
        {
          swap(i,j);
          times_sorted++;
          sorted = false;
        }
      }
    }
    pass++;
}
  return times_sorted;
}

template<typename Comparator>
int CardShop::insertionSort(const Comparator &comp,const std::string &key)
{
  int times_sorted = 0;
  int current;
  for(int i = 1; i < item_count_; i++){
    current = i;
    if(key == "atk")
    {
      while(current > 0 && comp(getPointerTo(current) -> getItem() -> getAtk(), getPointerTo(current - 1) -> getItem() -> getAtk())){
        swap(current,current - 1);
        times_sorted++;
        current--;
      }
    }
    else if(key == "def"){
      while(current > 0 && comp(getPointerTo(current) -> getItem()-> getDef(), getPointerTo(current - 1) -> getItem() -> getDef())){
        swap(current, current - 1);
        times_sorted++;
        current--;
      }
    }
  }
  return times_sorted;
}
template<typename Comparator>
int CardShop::mergeSort(Comparator comp, std::string key)
{
  std::cout << "Will not be implemented" << std::endl;
  return 0;
}

template<typename Comparator>
int CardShop::quickSort(const Comparator &comp, const std::string &key)
{
  int times_sorted = 0;
  quickSort(comp, key, 0, item_count_ - 1, times_sorted);
  return times_sorted;
}

template<typename Comparator>
void CardShop::quickSort(const Comparator &comp, const std::string &key, int i, int j, int &times_sorted)
{
  if(i < j)
  {
    int p = partition(comp, key, i , j, times_sorted);
    quickSort(comp, key, i, p - 1, times_sorted);
    quickSort(comp, key, p + 1, j, times_sorted);
  }
}

template<typename Comparator>
int CardShop::partition(const Comparator &comp, const std::string &key, int i, int j, int &times_sorted)
{
  int index = i - 1;
  for(int jndex = i; jndex < j; jndex++)
  {
    if(key == "atk")
    {
      if(comp(getPointerTo(jndex) -> getItem() -> getAtk(), getPointerTo(j) -> getItem() -> getAtk()))
      {
        index++;
        swap(index, jndex);
        times_sorted++;
      }
    }
    else if(key == "def")
    {
      if(comp(getPointerTo(jndex) -> getItem() -> getDef(), getPointerTo(j) -> getItem() -> getDef()))
      {
        index++;
        swap(index, jndex);
        times_sorted++;
      }
    }
  }
  swap(index + 1, j);
  times_sorted++;
  return index + 1;
}

