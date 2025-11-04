#ifndef NANOUSD_ITERATORS_H
#define NANOUSD_ITERATORS_H

#include "nanousd-types.h"

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup Iterators Iterators
///
/// @brief Iterators providing access to arrays of types than cannot be
/// represented in C
///
/// @{

typedef struct nusd_prim_iterator_s* nusd_prim_iterator_t;
typedef struct nusd_property_iterator_s* nusd_property_iterator_t;
typedef struct nusd_attribute_iterator_s* nusd_attribute_iterator_t;
typedef struct nusd_relationship_iterator_s* nusd_relationship_iterator_t;
typedef struct nusd_relationship_targets_iterator_s*
    nusd_relationship_targets_iterator_t;
typedef struct nusd_token_array_iterator_s* nusd_token_array_iterator_t;
typedef struct nusd_asset_path_array_iterator_s*
    nusd_asset_path_array_iterator_t;

typedef struct nusd_string_array_iterator_s*
    nusd_string_array_iterator_t;

/// Advances the prim iterator to the next prim and returns its path.
///
/// @param iterator Valid prim iterator handle.
/// @param prim_path Output pointer that will contain the current prim's path if
/// available.
///
/// @return true if a prim is available and prim_path was set, false if
/// iteration is complete
///
/// @note iterator must not be null.
/// @note prim_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_prim_iterator_next(nusd_prim_iterator_t iterator,
                             char const** prim_path);

/// Destroys a prim iterator and releases associated resources.
///
/// @param iterator Valid prim iterator handle to destroy. Can be null (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_prim_iterator_destroy(nusd_prim_iterator_t iterator);

/// Advances the property iterator to the next property and returns its path and
/// type.
///
/// @param iterator Valid property iterator handle.
/// @param property_path Output pointer that will contain the current property's
/// path if available.
/// @param property_type Output pointer that will contain the current property's
/// type if available.
///
/// @return true if a property is available and outputs were set, false if
/// iteration is complete
///
/// @note iterator must not be null.
/// @note property_path must not be null.
/// @note property_type must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or
/// advanced.
/// @note For relationships, property_type will be set to
/// NUSD_TYPE_RELATIONSHIP.
NANOUSD_API
bool nusd_property_iterator_next(nusd_property_iterator_t iterator,
                                 char const** property_path,
                                 nusd_type_t* property_type);

/// Destroys a property iterator and releases associated resources.
///
/// @param iterator Valid property iterator handle to destroy. Can be null
/// (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_property_iterator_destroy(nusd_property_iterator_t iterator);

/// Advances the attribute iterator to the next attribute and returns its path.
///
/// @param iterator Valid attribute iterator handle.
/// @param attribute_path Output pointer that will contain the current
/// attribute's path if available.
///
/// @return true if an attribute is available and attribute_path was set, false
/// if iteration is complete
///
/// @note iterator must not be null.
/// @note attribute_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_attribute_iterator_next(nusd_attribute_iterator_t iterator,
                                  char const** attribute_path);

/// Destroys an attribute iterator and releases associated resources.
///
/// @param iterator Valid attribute iterator handle to destroy. Can be null
/// (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t
nusd_attribute_iterator_destroy(nusd_attribute_iterator_t iterator);

/// Advances the relationship iterator to the next relationship and returns its
/// path.
///
/// @param iterator Valid relationship iterator handle.
/// @param relationship_path Output pointer that will contain the current
/// relationship's path if available.
///
/// @return true if a relationship is available and relationship_path was set,
/// false if iteration is complete
///
/// @note iterator must not be null.
/// @note relationship_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_relationship_iterator_next(nusd_relationship_iterator_t iterator,
                                     char const** relationship_path);

/// Destroys a relationship iterator and releases associated resources.
///
/// @param iterator Valid relationship iterator handle to destroy. Can be null
/// (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t
nusd_relationship_iterator_destroy(nusd_relationship_iterator_t iterator);

/// Advances the relationship targets iterator to the next target and returns
/// its path.
///
/// @param targets Valid relationship targets iterator handle.
/// @param target_path Output pointer that will contain the current target's
/// path if available.
///
/// @return true if a target is available and target_path was set, false if
/// iteration is complete
///
/// @note targets must not be null.
/// @note target_path must not be null.
/// @note The returned path pointer is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_relationship_targets_iterator_next(
    nusd_relationship_targets_iterator_t targets, char const** target_path);

/// Destroys a relationship targets iterator and releases associated resources.
///
/// @param targets Valid relationship targets iterator handle to destroy. Can be
/// null (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_relationship_targets_iterator_destroy(
    nusd_relationship_targets_iterator_t targets);

/// Advances the token array iterator to the next token and returns its path.
///
/// @param tokens Valid token array iterator handle.
/// @param token Output pointer that will contain the current token if
/// available.
///
/// @return true if a token is available, false if iteration is complete
///
/// @note tokens must not be null.
/// @note token must not be null.
/// @note The returned token is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_token_array_iterator_next(nusd_token_array_iterator_t tokens,
                                    char const** token);

/// Returns the total number of tokens in a token array iterator.
///
/// @param iterator Valid token array iterator handle.
///
/// @return Number of tokens in the iterator.
///
/// @note iterator must not be null.
/// @note This function returns the total size regardless of the current
/// iteration position.
NANOUSD_API
size_t nusd_token_array_iterator_size(nusd_token_array_iterator_t iterator);

/// Destroys a token array iterator and releases associated resources.
///
/// @param tokens Valid token array iterator handle to destroy. Can be null
/// (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t
nusd_token_array_iterator_destroy(nusd_token_array_iterator_t tokens);

/// Advances the token array iterator to the next token and returns its path.
///
/// @param asset_paths Valid asset_path array iterator handle.
/// @param asset_path Output pointer that will contain the current asset_path if
/// available.
///
/// @return true if a asset_path is available, false if iteration is complete
///
/// @note asset_paths must not be null.
/// @note asset_path must not be null.
/// @note The returned asset_path is valid until the iterator is destroyed or
/// advanced.
NANOUSD_API
bool nusd_asset_path_array_iterator_next(
    nusd_asset_path_array_iterator_t asset_paths, char const** asset_path);

/// Returns the total number of asset_paths in a asset_path array iterator.
///
/// @param iterator Valid asset_path array iterator handle.
///
/// @return Number of asset_paths in the iterator.
///
/// @note iterator must not be null.
/// @note This function returns the total size regardless of the current
/// iteration position.
NANOUSD_API
size_t
nusd_asset_path_array_iterator_size(nusd_asset_path_array_iterator_t iterator);

/// Destroys a asset_path array iterator and releases associated resources.
///
/// @param asset_paths Valid asset_path array iterator handle to destroy. Can be
/// null (no-op).
///
/// @return NUSD_RESULT_OK on success
///
/// @note This function always returns NUSD_RESULT_OK.
/// @note After calling this function, the iterator handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null iterator handle.
NANOUSD_API
nusd_result_t nusd_asset_path_array_iterator_destroy(
    nusd_asset_path_array_iterator_t asset_paths);

/// Advances the string array iterator to the next string and returns it.
///
/// @param strings Valid string array iterator handle.
/// @param string_value Output pointer that will contain the current string if 
/// available.
///
/// @return true if a string is available and string_value was set, false if 
/// the iterator has reached the end or if an error occurred
///
/// @note strings must not be null.
/// @note string_value must not be null.
/// @note The returned string pointer is valid until the iterator is destroyed 
/// or advanced.
/// @note This function advances the iterator position, so subsequent calls 
/// will return different strings.
NANOUSD_API
bool nusd_string_array_iterator_next(
    nusd_string_array_iterator_t strings, char const** string_value);

/// Returns the total number of strings in a string array iterator.
///
/// @param iterator Valid string array iterator handle.
///
/// @return Number of strings in the iterator.
///
/// @note iterator must not be null.
/// @note This function returns the total size regardless of the current
/// iteration position.
NANOUSD_API
size_t
nusd_string_array_iterator_size(nusd_string_array_iterator_t iterator);

/// Destroys a string array iterator and releases associated resources.
///
/// @param strings Valid string array iterator handle to destroy. Can be
/// null (no-op).
///
/// @note After calling this function, the strings handle becomes invalid and
/// must not be used.
/// @note It is safe to call this function with a null strings handle.
NANOUSD_API
nusd_result_t nusd_string_array_iterator_destroy(
    nusd_string_array_iterator_t strings);

/// @}

#ifdef __cplusplus
}
#endif

#endif
