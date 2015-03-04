#ifndef _UTILITIES_H_
#define _UTILITIES_H_

template<typename T, typename U, typename V>
bool clamp_modify(T& value, U min, V max){
  if( value < min ){
    value = min;
    return true;
  } else if ( value > max){
    value = max;
    return true;
  } else {
    return false;
  }
}

template<typename T, typename U, typename V>
T clamp(T value, U min, V max){
  clamp_modify(value, min, max);
  return value;
}

template<typename T, typename... Params>
std::unique_ptr<T> make_unique(Params&&... params){
  return std::unique_ptr<T>(new T(std::forward<Params>(params)...));
}

#endif /* _UTILITIES_H_ */
