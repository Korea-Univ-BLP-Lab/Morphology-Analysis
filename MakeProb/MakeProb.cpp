#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MakeFST(const char *SourceFilename, const char *DataFilename, const char *FSTFilename);

void PrintUsage(char *Program)
{

  fprintf(stderr, "Probability data compilation program\n");
  fprintf(stderr, " USAGE : %s <Text Probability> <FST Filename> <DATA Filename>\n", Program);
  fprintf(stderr, "    ex) %s prob.txt prob.FST prob.dat\n\n", Program);
}


int main(int argc, char *argv[])
{
  if (argc!=4) {
    PrintUsage(argv[0]);
    return 1;
  }
  MakeFST(argv[1], argv[3], argv[2]);
  return 0;
}
