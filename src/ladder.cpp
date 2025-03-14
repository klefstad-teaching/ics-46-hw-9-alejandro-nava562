#include "ladder.h"

void error(string word1, string word2, string msg) {
  cerr << "Error: " << msg << " (" << word1 << ", " << word2 << ")" << endl;
}

bool edit_distance_within(const std::string &str1, const std::string &str2,
                          int d) {
  int len1 = str1.size(), len2 = str2.size();
  if (abs(len1 - len2) > d)
    return false;

  int diff = 0, i = 0, j = 0;
  while (i < len1 && j < len2) {
    if (str1[i] != str2[j]) {
      diff++;
      if (diff > d)
        return false;
      if (len1 > len2)
        i++;
      else if (len1 < len2)
        j++;
      else {
        i++;
        j++;
      }
    } else {
      i++;
      j++;
    }
  }
  return true;
}

bool is_adjacent(const string &word1, const string &word2) {
    return edit_distance_within(word1, word2, 1);
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        cerr << "Error: Unable to open " << file_name << endl;
        return;
    }
    string word;
    while (file >> word) {
        word_list.insert(word);
    }
}