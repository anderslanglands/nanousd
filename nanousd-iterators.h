#ifndef NANOUSD_ITERATORS_H
#define NANOUSD_ITERATORS_H

#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct nusd_prim_iterator_s* nusd_prim_iterator_t;
typedef struct nusd_property_iterator_s* nusd_property_iterator_t;
typedef struct nusd_attribute_iterator_s* nusd_attribute_iterator_t;
typedef struct nusd_relationship_iterator_s* nusd_relationship_iterator_t;
typedef struct nusd_relationship_targets_iterator_s* nusd_relationship_targets_iterator_t;

/// Advances the prim iterator to the next prim and returns its path.
/// 
/// @param iterator Valid prim iterator handle.
/// @param prim_path Output pointer that will contain the current prim's path if available.
/// 
/// @return true if a prim is available and prim_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note prim_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator, char const** prim_path);

/// Destroys a prim iterator and releases associated resources.
/// 
/// @param iterator Valid prim iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator);

/// Advances the property iterator to the next property and returns its path and type.
/// 
/// @param iterator Valid property iterator handle.
/// @param property_path Output pointer that will contain the current property's path if available.
/// @param property_type Output pointer that will contain the current property's type if available.
/// 
/// @return true if a property is available and outputs were set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note property_path must not be null.
/// @note property_type must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
/// @note For relationships, property_type will be set to NUSD_TYPE_RELATIONSHIP.
NANOUSD_API
bool nusd_property_iterator_next(nusd_property_iterator_t iterator, char const** property_path, nusd_type_t* property_type);

/// Destroys a property iterator and releases associated resources.
/// 
/// @param iterator Valid property iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_property_iterator_destroy(nusd_property_iterator_t iterator);

/// Advances the attribute iterator to the next attribute and returns its path.
/// 
/// @param iterator Valid attribute iterator handle.
/// @param attribute_path Output pointer that will contain the current attribute's path if available.
/// 
/// @return true if an attribute is available and attribute_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note attribute_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator, char const** attribute_path);

/// Destroys an attribute iterator and releases associated resources.
/// 
/// @param iterator Valid attribute iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator);

/// Advances the relationship iterator to the next relationship and returns its path.
/// 
/// @param iterator Valid relationship iterator handle.
/// @param relationship_path Output pointer that will contain the current relationship's path if available.
/// 
/// @return true if a relationship is available and relationship_path was set, false if iteration is complete
/// 
/// @note iterator must not be null.
/// @note relationship_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator, char const** relationship_path);

/// Destroys a relationship iterator and releases associated resources.
/// 
/// @param iterator Valid relationship iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator);

/// Advances the relationship targets iterator to the next target and returns its path.
/// 
/// @param targets Valid relationship targets iterator handle.
/// @param target_path Output pointer that will contain the current target's path if available.
/// 
/// @return true if a target is available and target_path was set, false if iteration is complete
/// 
/// @note targets must not be null.
/// @note target_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or advanced.
NANOUSD_API
bool nusd_relationship_targets_iterator_next(nusd_relationship_targets_iterator_t targets, char const** target_path);

/// Destroys a relationship targets iterator and releases associated resources.
/// 
/// @param targets Valid relationship targets iterator handle to destroy. Can be null (no-op).
/// 
/// @return NUSD_RESULT_OK on success
/// 
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_relationship_targets_iterator_destroy(nusd_relationship_targets_iterator_t targets);

#ifdef __cplusplus
}
#endif

#endif
