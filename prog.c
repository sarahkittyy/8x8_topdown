#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>

void a(unsigned char *k, unsigned char n) {
  n %= (!0 << (!0 + !0 + !0));
  (*k) &= ~(((!0) << 0) | ((!0) << (!0)) |
            ((!0) << (!0 ^ ((!0 << !0) | (!0)) | (!0 + !0))));
  (*k) |= n;
}

unsigned char do_something(unsigned char k) {
  return (k & ((!0) << 0)) + (k & ((!0) << (!0))) +
         (k & ((!0) << (!0 ^ ((!0 << !0) | (!0)) | (!0 + !0))));
}

void c(unsigned char *k, unsigned char n) {
  n %= (!0 << (!0 + !0 + !0));
  (*k) &=
      ~(((!0) << ((!0 << !0) | (!0))) | ((!0) << ((!0 + !0) << (!0))) |
        ((!0) << ((((!0 << (!0)) | (!0 << (!0 + !0))) | (!0)) ^ (!0 + !0))));
  (*k) |= (n << ((!0 << !0) | (!0)));
}

unsigned char d(unsigned char k) {
  return ((k & ((!0) << ((!0 << !0) | (!0)))) >> ((!0 << !0) | (!0))) +
         ((k & ((!0) << ((!0 + !0) << (!0)))) >> ((!0 << !0) | (!0))) +
         ((k & ((!0) << ((((!0 << (!0)) | (!0 << (!0 + !0))) | (!0)) ^
                         (!0 + !0)))) >>
          ((!0 << !0) | (!0)));
}

void fd(unsigned char *k, unsigned char o) {
  (*k) &= ~(((!0 << !0) | (!0)) << (((!0 + !0) << (!0 + !0)) - (!0 + !0)));
  (*k) |= (o << (((!0 + !0) << (!0 + !0)) - (!0 + !0)));
}

unsigned char hd(unsigned char k) {
  return (k &
          (((!0 << !0) | (!0)) << (((!0 + !0) << (!0 + !0)) - (!0 + !0)))) >>
         (((!0 + !0) << (!0 + !0)) - (!0 + !0));
}

void q(unsigned char *k) {
  hd(*k) ? (hd(*k) - (!0) ? (hd(*k) - (!0 ^ ((!0 << !0) | (!0)) | (!0 + !0))
                                 ? (c(k, d(*k) + (!0)))
                                 : (a(k, do_something(*k) + (!0))))
                          : (a(k, do_something(*k) - (!0))))
         : (c(k, d(*k) - (!0)));
}

void p(unsigned char k) {
  printf("@@@@@@@@@@\n@");
  for (int _ = 0; _ < (!0 << (!0 + !0 + !0)); ++_) {
    for (int __ = 0; __ < (!0 << (!0 + !0 + !0)); ++__) {
      if (!(do_something(k) - __) && d(k) == _) {
        printf("o");
      } else
        printf("-");
    }
    printf("@\n@");
  }
  puts("@@@@@@@@@");
}

int main() {

  struct termios old_tio, new_tio;
  unsigned char c;

  // get the terminal settings for stdin
  tcgetattr(STDIN_FILENO,&old_tio);

  // we want to keep the old setting to restore them a the end
  new_tio=old_tio;

  // disable canonical mode (buffered i/o) and local echo
  new_tio.c_lflag &=(~ICANON & ~ECHO);

  // set the new settings immediately
  tcsetattr(STDIN_FILENO,TCSANOW,&new_tio);

  puts("use wasd");
  unsigned char k = 0;
  p(k);

  char in;
  do {
    in = getchar();
    if(in == 'w') {
      fd(&k, 0);
    } else if(in == 'a') {
      fd(&k, 1);
    } else if(in == 's') {
      fd(&k, 3);
    } else if(in == 'd') {
      fd(&k, 2);
    }

    q(&k);
    p(k);
  } while(in != 'q');

  /* restore the former settings */
  tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);

  return 0;
}
