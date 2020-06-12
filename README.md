# CSTL

## 규칙

1. 구조체의 이름은 PascalCase 입니다.
2. (매크로)함수의 이름은 snake_case 입니다.
3. (매크로)함수의 인자 순서는 다음과 같습니다.
   1. 타입(`*`을 포함하면 안됨, `typedef`를 사용할것)
   2. (필요시)자기 자신
   3. (필요시)색인
   4. (필요시)값
3. 인자 `P1`, `P2`, ...를 받아 `T` 타입의 결과를 반환하는 (매크로)함수 `f`는 `f(P1, P2, ...) -> T`와 같이 표시합니다.
4. `_apply`가 붙은 (매크로)함수는 원본을 수정합니다.
5. 이름 앞에 `$`이 붙어있는 (매크로)함수는 실패를 염두에 둔 `_safe` 버전을 같이 제공합니다. 예를 들어, `vec_at(T, S, I) -> T`와 `vec_at_safe(T, S, I) -> Option(T)`가 제공되고, `vec_insert_apply(T, S, I, V) -> void`와 `vec_insert_apply_safe(T, S, I, V) -> bool`가 제공됩니다. 성공시 `true`, 실패시 `false`를 반환합니다.
6. 이름 앞에 `@`이 붙어있는 구조체나 (매크로)함수는 구현 예정입니다.

## 구조체, (매크로)함수 목록

1. `utility`
    1. `option.h`
        1. `Option(T)`
        2. `none(T) -> Option(T)`
        3. `some(T, V) -> Option(T)`
        4. `option(T, ...) -> Option(T)`
    2. `result.h`
        1. `Result(T, U)`
        2. `ok(T, U, V) -> Result(T, U)`
        3. `err(T, U, V) -> Result(T, U)`
2. `container`
    1. `vec.h`
        1. `Vec(T)`
        2. `vec1(T) -> Vec(T)`
        3. `vec2(T, C) -> Vec(T)`
        4. `vec3(T, C, V) -> Vec(T)`
        4. $`vec_at(T, S, I) -> T`
        5. $`vec_back(T, S) -> T`
        6. `vec_begin(T, S) -> T*`
        7. `vec_end(T, S) -> T*`
        8. `vec_empty(T, S) -> bool`
        9. `vec_reserve_apply(T, S, V) -> void`
        10. `vec_shrink_apply(T, S) -> void`
        11. `vec_resize_apply(T, S, V) -> void`
        12. `vec_clear_apply(T, S) -> void`
        13. $@`vec_insert_apply(T, S, I, V) -> void`
        14. $@`vec_erase_apply(T, S, I, V) -> void`
        15. @`vec_push_back_apply(T, S, V) -> void`
        16. $@`vec_pop_back_apply(T, S) -> void`
        17. @`vec_clone(T, S) -> Vec(T)`
        17. `vec_destructor(T, S) -> void`
