#pragma once

typedef struct _trie trie;

/**
 * @brief  Returns a pointer to a trie
 * @note   yout may have call for destroy_trie to free the used memory
 * @retval recent allocated trie pointer
 */
trie *create_trie();

/**
 * @brief  Deallocates a 
 * @note   
 * @param  *t: 
 * @retval None
 */
void trie_destroy(trie *t);

/**
 * @brief  Returns the word's id
 * @param  *root: pointer to the trie's root
 * @param  *word: contains the word wich id will be search
 * @retval word's id
 */
int get_id(trie *root, char *word, int insert);

/**
 * @brief  Returns a word based on it's id
 * @note   make sure that the id is valid. Otherwise, a undefined behavior may occur.  
 * @param  *t: pointer to a trie
 * @param  id: id of the word that we're looking for
 * @retval pointer to a string containing the word
 */
char *get_word(trie *t, int id);
