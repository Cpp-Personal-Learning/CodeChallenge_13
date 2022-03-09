// CodeChallenge_13.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include<cerrno>
#include<cstdio>
#include <cstring>
#include <cstdlib>

using namespace std;
#pragma warning(disable : 4996)

constexpr size_t max_string = 1024;
constexpr size_t name_size = 32;
constexpr size_t desc_size = 128;
constexpr size_t max_split = 15;

char tab_char = '\t';
constexpr char const* filename = "C:/Users/catal/Zealand/SEMESTERS/4TH SEMESTER/Personal Learning/C++/Challenges/CodeChallenge_13/items.txt";
struct Item
{
    int SKU;
    char name[name_size];
    char description[desc_size];
};

// str_seps(s) -- returns an array where each element
// represents the position of a separator in the string
// first element is a count
size_t *str_steps(const char* s, size_t len)
{
    static size_t indicies[max_split + 1];
    size_t & count = indicies[0];
    if (len > 3) return indicies;
    for (size_t& z : indicies) z = 0;
    for (size_t i = 0; i < len; ++i) {
        if (s[i] == tab_char) {
            ++count;
            indicies[count] = i;      //where tab is met, the count increases(1st/2nd tab) and we get the index (i)
            if (count >= max_split) break;
        }
    }
    return indicies;
}

int main()
{
    char buf[max_string];   // buffer for reading lines in file

    FILE* fr = fopen(filename,"r");
    if(!fr)
    {
        const char* errstr = strerror(errno);
        printf("cannot open file (%d): %s\n", errno, errstr);
        return 1;
    }

    while ((fgets(buf,max_string,fr)))
    {
        size_t len = strnlen(buf, max_string);
        if (len <= 5) continue;

        //trim newline/endl from the end of the string
        if(buf[len-1]=='\n')
        {
            buf[len - 1] == 0;
            --len;
        }

        size_t* split3 = str_steps(buf, len); //pointer to original string
        if (split3[0] < 2) break; //if the first tab is in 1/2nd position of the string
        buf[split3[1]] = buf[split3[2]] = 0; //change separators to terminators

        Item current_item;
        current_item.SKU = atoi(buf); //atoi converts to integer
        strncpy(current_item.name, buf + split3[1] + 1, name_size - 1);
        strncpy(current_item.description, buf + split3[2] + 1, desc_size - 1);

        printf("sku: %d, name: %s, desc: %s\n", current_item.SKU, current_item.name, current_item.description);
    }
    return 0;
}
	//get a line
    //get first tab
    //get second tab
    //get last part, remove 0.