#include <stdio.h>

int find_if_comment(char* line){
  int linesize = sizeof(line)/sizeof(line[0]);
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

    if(setMultiLine){
      continue;
    }

      
    printf("%s",buf );
  }
  fclose(fp);
  return 0;
}
