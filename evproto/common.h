#ifndef EVPROTO_COMMON_H
#define EVPROTO_COMMON_H

#define EVPROTO_DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                            \
  void operator=(const TypeName&)

#endif  // EVPROTO_COMMON_H
