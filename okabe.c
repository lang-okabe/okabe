#include <stdio.h>

// Return codes are used to find comments and empty lines
// rc : meaning
// 1  : Line starts with  //
// 2  : Line starts with /* (start of a multiline comment)
//-2  : Line starts with */ (end of a multine)
// 3  : Line is just a empty \n

int find_if_comment(char* line){
  int linesize = sizeof(line)/sizeof(line[0]);
  if(line[0] == '\n')    { return 3; }

  for (int i = 0; i < linesize; ++i) {
    if('/' == line[i]){
      if(line[i+1] == '/'){
	return 1;
      }
      if(line[i+1] == '*' ){
	return 2;
      }
      if(line[i-1] == '*'){
	return -2;
      }
    }
  }
  return 0;
}

/* Find Typedefs and Substiture macros all over the file */
int find_if_macro(char* line){
  
}


int main()
{
  FILE *fp = fopen("main.ok", "r");
    if (fp == NULL) {
    printf("[ERR] opening file");
    return -1;
  }
  char buf[99];
  bool setMultiLine = false; 

  while(fgets(buf, 99, fp)){


    int find_comm = find_if_comment(buf);
    if(find_comm == 1){
      continue;
    }
    if(find_comm == 2){
      setMultiLine = true;
      continue;
    } else if (find_comm == -2) {
	setMultiLine = false;
	continue;
    }
    if(find_comm == 3){
      continue;
    }

    if(find_comm == 4){
      printf("%d", find_comm);
    }

    
    if(setMultiLine){
      continue;
    }

      
    printf("%s",buf );
  }
  fclose(fp);
  return 0;
}
