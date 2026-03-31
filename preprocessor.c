
#include <stdio.h>
#include <string.h>


/* SET OF GLOBAL VARIABLES */
bool setMultiLine = false;


bool starts_with(char* keyword, char* line){
  int size = strlen(keyword);
  for (int i = 0; i < size; ++i) {
    if(keyword[i] != line[i]){
      return false;
    }
  }

  return true;
}

// Return codes are used to find comments and empty lines
// rc : meaning
// 1  : Line starts with  //
// 2  : Line starts with /* (start of a multiline comment)
//-2  : Line starts with */ (end of a multine)
// 3  : Line is just a empty \n

int find_if_comment(char* line){
  int linesize = sizeof(line)/sizeof(line[0]);
  if(line[0] == '\n')    { return 3; }
  if(starts_with("//",line)){
    return 1;
  }
  if(starts_with("/*", line)){
    return 2;
  }
  if(starts_with("*/", line)){
    return -2;
  }  
  return 0;
}

/* Find Typedefs and Substiture macros all over the file */
bool find_if_macro(char* line){
  if(starts_with("typedef", line)){
    printf("replace %s" , line);
    return true;
  }
  return false;
}

/* Remove all the comments  */
bool rm_comments(char* buf){

    /* FIND COMMENTS */
    int find_comm = find_if_comment(buf);
    if(find_comm == 1 || find_comm == 3){
      return true;
    }
    if(find_comm == 2){
      setMultiLine = true;
      return true;
    } else if (find_comm == -2) {
	setMultiLine = false;
	return true;
    }
    
    if(setMultiLine){
      return true;
    }
    /* END COMMENTS */
}

int main()
{
  FILE *fp = fopen("main.ok", "r");
    if (fp == NULL) {
    printf("[ERR] opening file");
    return -1;
  }

    char buf[99];

  while(fgets(buf, 99, fp)){
    if (rm_comments(buf)){
      continue;
    }
    if (find_if_macro(buf)) {
	continue;
      }

    printf("%s", buf);
  }
  fclose(fp);
  return 0;
}
