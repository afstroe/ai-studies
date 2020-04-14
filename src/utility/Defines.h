#ifndef __DEFINES_H__
#define __DEFINES_H__

#define STD_VECTOR(TYPE, VECTOR_TYPE_NAME) VECTOR_TYPE_NAME<TYPE, std::allocator<TYPE>>
#define TEMPLATE_TYPE_STD_VECTOR(TEMPLATE_NAME) template <class, class> class TEMPLATE_NAME

#define FOR(index, cap) for(auto index = 0; index < cap; ++index)

#define DECLARE_PROTECTED_TRIVIAL_ATTRIBUTE_C(TYPE, NAME)   \
  protected:                                                \
    TYPE _##NAME;                                           \
  public:                                                   \
    /*! <br>                                                \
      \brief getter / setter for _##NAME <br>               \
      \return a reference to _##NAME <br>                   \
      */                                                    \
    TYPE& NAME() { return _##NAME; }                        \
                                                            \
  /*! <br>                                                  \
    \brief getter for _##NAME <br>                          \
    \return a constant reference to _##NAME <br>            \
    */                                                      \
  const TYPE& NAME() const { return _##NAME; }

#endif // !__DEFINES_H__

