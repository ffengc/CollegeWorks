#define _CRT_SECURE_NO_WARNINGS 1

#ifdef __cplusplus

#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

#elif
#endif


/**
 * 将句子拆分成三个vector，分别存储单词，整数和浮点数。.
 */

template<class T>
void print_vector(vector<T>& v) {
	typename vector<T>::iterator it = v.begin();
	while (it != v.end()) {
		cout << *it << " ";
		it++;
	}
}
void split_sentence(const string& s, const string& sep, vector<int>& vint, vector<double>& vdouble, vector<string>& vs) {
	string::size_type wordStartPos = s.find_first_not_of(sep);
	while (wordStartPos != string::npos) { //a new word detected
		//a word must end before a separator
		string::size_type wordEndPos = s.find_first_of(sep, wordStartPos);
		string word;
		if (wordEndPos != string::npos) { //in the middle of the string
			word.assign(s, wordStartPos, wordEndPos - wordStartPos);
		}
		else { //hit the end of the string;string::npos means until the end
			word.assign(s, wordStartPos, string::npos);
		}
		if (isalpha(word[0])) {
			vs.push_back(word);
		}
		else {
			if (word.find('.') != string::npos)
				vdouble.push_back(stod(word));
			else
				vint.push_back(stoi(word));
		}
		//now search the next word
		wordStartPos = s.find_first_not_of(sep, wordEndPos);
	}
}
int main(){
	string blackHole = "EHT measured the black hole's mass to be approxximately\
		6.5billion solar masses and measured the diameter of its event horizon to\
		be approximately 40 billion kilometres (270 AU; 0.0013 pc;0.0042 ly";
	vector<int>intVec;
	vector<double>doubleVec;
	vector<string>wordVec;

	string separators = " ();";//分隔符

	split_sentence(blackHole, separators, intVec, doubleVec, wordVec);

	print_vector(intVec);
	cout << endl << endl;
	print_vector(doubleVec);
	cout << endl << endl;
	print_vector(wordVec);
	return 0;
}