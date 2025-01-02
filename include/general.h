#ifndef GENERAL_H
#define GENERAL_H

#define MODIFY_REG(REG, MASK, DATA) ((REG &= ~MASK) \
                                     (REG |= DATA))

#endif GENERAL_H
