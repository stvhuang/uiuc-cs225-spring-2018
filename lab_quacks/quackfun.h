/**
 * @file quackfun.h
 * Contains the QuackFun namespace definition.
 */

#ifndef STACKFUN_H
#define STACKFUN_H

#include <queue>
#include <stack>

using std::queue;
using std::stack;

/**
 * Namespace to contain the stack and queue functions for this lab.
 */
namespace QuackFun {
template <typename T>
T sum(stack<T> &s);

bool isBalanced(queue<char> input);

template <typename T>
void scramble(queue<T> &q);

template <typename T>
bool verifySame(stack<T> &s, queue<T> &q);
};  // namespace QuackFun

#include "quackfun.cpp"
#endif
