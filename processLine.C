void processLine(const char *line, const char *lib=0){
//  if( lib ) gSystem->Load(lib,"Ok");
  if( lib ) gSystem->Load(lib);
  gROOT->ProcessLine(line);
}
