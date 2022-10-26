#include <cstdio>
#define LINE_SIZE 500
bool ExecPreprocesor( const char * NazwaPliku, istringstream &IStrm4Cmds )
{
string Cmd4Preproc = ”cpp -P ”;
char Line[LINE_SIZE];
ostringstream OTmpStrm;
Cmd4Preproc += NazwaPliku;
FILE* pProc = popen(Cmd4Preproc.c str(),”r”);
if (!pProc) return false;
while (fgets(Line,LINE_SIZE,pProc)) {
OTmpStrm << Line;
}
IStrm4Cmds.str(OTmpStrm.str());
return pclose(pProc) == 0;
}
