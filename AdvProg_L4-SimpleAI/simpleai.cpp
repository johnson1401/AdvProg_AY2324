int readMaxGuess()
{
    int maxGuess;
    cout << endl << "Enter the number of incorrect guesses: "; // Yêu cầu người dùng nhập số lần đoán sai tối đa
    cin >> maxGuess;
    return maxGuess;
}

int readWordLen()
{
    int wordLen;
    cout << endl << "Enter the number characters of your secret word: "; // Yêu cầu người dùng nhập số ký tự của từ bí mật
    cin >> wordLen;
    return wordLen;
}

vector<string> filterWordsByLen(int wordLen, const vector<string>& vocabulary)
{
    vector<string> answer;

    for (auto &word: vocabulary)
        if (int(word.length()) == wordLen) answer.push_back(word); // Lọc các từ có độ dài bằng wordLen từ từ vựng và đưa vào vector kết quả

    return answer;
}

char nextCharWhenWordIsNotInDictionary(const set<char>& selectedChars)
{
    char answer = 'a'; // Trả về ký tự 'a' mặc định khi từ không có trong từ điển
    return answer;
}

map<char, int> countOccurrences(const vector<string>& candidateWords)
{
    map<char, int> answer;
    for (auto word: candidateWords)
        for (auto ch: word)
            answer[ch] ++; // Đếm số lần xuất hiện của các ký tự trong tập hợp các từ ứng viên

    return answer;
}

char findMostFrequentChar(const map<char, int>& occurrences, const set<char>& selectedChars)
{
    char answer = ' ';
    int maxOccurence = 0;
    for (char ch = 'a'; ch <= 'z'; ch ++)
    {
        if (selectedChars.find(ch) != selectedChars.end()) continue; // Bỏ qua các ký tự đã được chọn trước đó
        for (auto mapPair: occurrences)
        {
            if (mapPair.first == ch && mapPair.second > maxOccurence)
            {
                maxOccurence = mapPair.second;
                answer = ch; // Tìm ký tự xuất hiện nhiều nhất trong tập hợp các từ ứng viên
            }
        }
    }
    return answer;
}

char findBestChar(const vector<string>& candidateWords, const set<char>& selectedChars)
{
    char answer;
    map<char, int> occurrences = countOccurrences(candidateWords);
    answer = findMostFrequentChar(occurrences, selectedChars); // Tìm ký tự tốt nhất để dự đoán dựa trên số lần xuất hiện của các ký tự trong tập hợp các từ ứng viên
    return answer;
}

string getWordMask(char nextChar)
{
    string mask;
    cout << "The next char is: " << nextChar << endl; // Hiển thị ký tự tiếp theo cần dự đoán
    cout << "Please give me your answer: ";
    cin >> mask; // Nhập mask từ người dùng
    return mask;
}

bool isCorrectChar(char ch, const string& mask)
{
    bool answer = 0;
    for (auto curCh: mask)
        if (curCh == ch)
        {
            answer = 1; // Kiểm tra xem ký tự dự đoán có chính xác không
        }
    return answer;
}

bool isWholeWord(const string& mask)
{
     bool answer = 1;
    for (auto ch: mask)
        if (ch < 'a' || ch > 'z') answer = 0; // Kiểm tra xem mask có phải là từ hoàn chỉnh không
    return answer;
}

bool wordConformToMask(const string& word, const string& mask, char ch)
{
    bool answer = 1;
    for (int pos = 0; pos < int(word.size()); pos ++)
        if (mask[pos] != '-' && word[pos] != mask[pos]) answer = 0; // Kiểm tra xem từ có phù hợp với mask và ký tự dự đoán không
    return answer;
}

vector<string> filterWordsByMask(const vector<string>& words, const string& mask, char ch)
{
    vector<string> answer;
    for (auto curWord: words)
    {
        if (wordConformToMask(curWord, mask, ch))
            answer.push_back(curWord); // Lọc các từ thỏa mãn mask và ký tự dự đoán
    }
    return answer;
}
