#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

int GetWindowWidth();
int GetWindowHeight();

void ErrorMsg(const char* message);
void Message(const char* message);
void WarnMsg(const char* message);

#ifdef __cplusplus
}
#endif

#endif