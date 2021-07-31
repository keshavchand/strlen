#include <immintrin.h>
#include <assert.h>
#include <emmintrin.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <intrin.h>

#define print_and_exec(delim , func) printf( #func " " delim "\n" , func)

#define increment_len 256/8
typedef union{
	__int8 c[increment_len];
	__m256i i;
} char32;

char * test(char* );

int strlen_intrin(const char * cstr){
	//Find '0' in the character sequence;
	
	char32 res;
	int len = 0;
	__m256i null_byte = _mm256_set1_epi8(0);
	while(true){
		__m256i some_string = _mm256_loadu_epi8((void const*) (cstr + len));
		res.i = _mm256_cmpeq_epi8(some_string, null_byte);

    __int64 mask = _mm256_movemask_epi8(res.i);
		if (mask == 0){
			len += increment_len;
			continue;
		}

    //TODO: Currently even next character is incremented sequencially;
    //need to do that in one instruction;
    //maybe counting no of significant zeros in mask?
    for(char i = *(cstr + len); i != 0; i = *(cstr + len)){
      len ++ ;
    }
    return len;
	}

}

#include <stdlib.h>
#include <time.h>

int main(){
  char *cstr = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
  cstr = test((char *)cstr);
  
	clock_t volatile start;
  clock_t volatile end;
  {
    start = clock();
    int volatile hw;
    for (int i = 0 ; i < 100000 ; i++){
      hw = strlen_intrin(cstr);
      assert(hw == 255 * 2);
    }
    end = clock();
    print_and_exec("%d ", end-start);
  }
  {
    start = clock();
    int volatile hw;
    for (int i = 0 ; i < 100000 ; i++){
      hw = strlen(cstr);
      assert(hw == 255 * 2);
    }
    end = clock();
    print_and_exec("%d ", end-start);
  }
	return 0;
}


