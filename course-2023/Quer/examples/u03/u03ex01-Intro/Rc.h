//
// Created by giuseppe on 15/03/23.
//

#ifndef U03EX01_INTRO_RC_H //     To avoid multiple inclusion of the same header file
#define U03EX01_INTRO_RC_H


class Rc {
public:
    int get_code(); // Definition of the function better in cpp file
    void set_code(int);

private:
    int code;

    friend class Rc2;
};

class Rc2{
public:
    int get_code(Rc);
};
#endif //U03EX01_INTRO_RC_H
