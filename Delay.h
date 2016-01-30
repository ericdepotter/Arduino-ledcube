//=================================
// include guard
#ifndef __DELAY_H_INCLUDED__
#define __DELAY_H_INCLUDED__

class NonBlockDelay {
    unsigned long iTimeout;
  public:
    void delay (unsigned long);
    bool timeout (void);
    unsigned long time(void);
};

#endif // __DELAY_H_INCLUDED__
