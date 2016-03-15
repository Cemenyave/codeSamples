/**
 * This simple program is just a demonstration for Darray (dynamic lenght array)
 * and String classes. It reads content of lorum_ipsum.txt file, stores it in the
 * array word by word and prints each word on separate line in command line output.
 */


#include <iostream>
#include <fstream>

#include "string.h"
#include "darray.h"

///
/// Slice word from source and shink sourse.
///
String getWord(String &source);

int main(void) {
  Darray<String> words;
  std::ifstream textFile;

  textFile.open("lorum_ipsum.txt");

  //read lorum_ipsum.txt by string then by word
  //and store in ot the array "words"
  bool endOfFile = false;
  while (!endOfFile) {
    String textString;
    textFile >> textString;
    endOfFile = textString.size() == 0;

    if (endOfFile) {
      break;
    }

    bool endOfLine = false;
    while (!endOfLine) {
      String word = getWord(textString);
      if (word.size()) {
        words.push(word);
      } else {
        endOfLine = true;
      }
    }
  }

  //print all words
  for (int i = 0; i < words.size(); ++i) {
    std::cout << words[i] << std::endl;
  }

  return 0;
}

String getWord(String &source) {
  size_t delimetrPosition = source.find(' ');
  String result{source.substr(0, delimetrPosition)};

  //coutn whitespaces
  int whitespaceCount = 0;
  if (source.size() > delimetrPosition) {
    while (source[ delimetrPosition + whitespaceCount ] == ' ') {
      ++whitespaceCount;
    }
  }

  //shrink 
  source = source.substr(delimetrPosition + whitespaceCount);
  return result;
}
