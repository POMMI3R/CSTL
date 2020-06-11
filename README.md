# CSTL

## 규칙

1. 구조체의 이름은 PascalCase 입니다.
2. (매크로)함수의 이름은 snake_case 입니다.
3. (매크로)함수의 인자 순서는 다음과 같습니다.
   1. 타입
   2. (필요시)자기 자신
   3. (필요시)색인
   4. (필요시)값
3. 인자 `P1`, `P2`, ...를 받아 `T` 타입의 결과를 반환하는 (매크로)함수 `f`는 `f(P1, P2, ...) -> T`와 같이 표시합니다.
4. 목록의 모든 (매크로)함수들은 원본을 수정하지 않으나, 이름 앞에 `*`이 붙어있는 (매크로) 함수들은 원본을 수정하는 `_apply` 버전을 같이 제공합니다. 예를 들어, `vec_push_back(T, S, V) -> Vec(T)`와 `vec_push_back_apply(T, S, V) -> void`가 제공됩니다.


## 구조체, (매크로)함수 목록

1. utility
    1. option.h
        1. `Option(T)`
        2. `none(T) -> Option(T)`
        3. `some(T, V) -> Option(T)`
        4. `option(T, ...) -> Option(T)`
    2. result.h
        1. `Result(T, U)`
        2. `ok(T, U, V) -> Result(T, U)`
        3. `err(T, U, V) -> Result(T, U)`
2. container
    1. vec.h
        1. `Vec(T)`
        2. `vec1(T) -> Vec(T)`
        3. `vec2(T, C, V) -> Vec(T)`
        4. `vec_at(T, S, I) -> T`
        5. `vec_back(T, S) -> T`
        6. `vec_begin(T, S) -> T*`
        7. `vec_end(T, S) -> T*`
        8. `vec_empty(T, S) -> bool`
        9. *`vec_reserve(T, S, V) -> Vec(T)`
        10. *`vec_shrink(T, S) -> Vec(T)`
        11. *`vec_resize(T, S, V) -> Vec(T)`
        12. *`vec_clear(T, S) -> Vec(T)`
        13. *`vec_insert(T, S, I, V) -> Vec(T)`
        14. *`vec_erase(T, S, I, V) -> Vec(T)`
        15. *`vec_push_back(T, S, V) -> Vec(T)`
        16. *`vec_pop_back(T, S, V) -> Vec(T)`
