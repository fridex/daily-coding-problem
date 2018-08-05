#!/usr/bin/env python3

import typing
from collections import deque


class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

    def __str__(self):
        """Serialize tree into a string - this solution uses a recursion, it might cause exceptions for large trees."""
        # We need to keep left/right explicitly set or pass as kwargs
        # so that empty left/right does not cause problems.
        return f"Node('{self.val}', left={str(self.left)}, right={str(self.right)})"


def serialize(n: Node) -> str:
    """Serialize the given tree given by a root node into a string."""
    stack1 = deque()
    stack2 = deque()

    stack1.append(n)

    result = ''
    brackets_count = 0
    while stack1 or stack2:
        if stack1:
            node = stack1.pop()

            if isinstance(node, Node):
                result += f"Node('{node.val}', left="
                stack1.append(node.left)
                stack2.append(node)
            elif node is None:
                result += "None"
            else:
                raise ValueError(f"Invalid node: {node} (type: {type(node)}")
        else:
            # We are getting back - continue from the marker stored in stack2.
            node = stack2.pop()
            if isinstance(node.right, Node):
                result += ", right="
                stack1.append(node.right)
                brackets_count += 1
            elif node.right is None:
                result += ", right=None)"
            else:
                raise ValueError(f"Invalid node: {node} (type: {type(node)}")

    result += "".join(")" * brackets_count)

    return result


def _parse_node_start(input_string: str) -> typing.Tuple[object, str, bool]:
    """Parse 'Node(val, ' part of the input string."""
    if input_string.startswith('None'):
        return None, input_string[len('None'):], True

    if input_string.startswith('Node('):
        input_string = input_string[len('Node('):]

    parts = input_string.lstrip().split(',', maxsplit=1)
    if parts != 2:
        raise ValueError("Invalid input")

    value, input_string = parts[0], input_string.lstrip()

    if not input_string.startswith('left='):
        # Whitespace sensitive.
        raise ValueError("Left expected")

    return value, input_string[len('left='):], False


def deserialize(input_string: str) -> typing.Optional[Node]:
    """Deserialize the given input string to a tree."""
    # The main problem here is when creating Node using kwargs - in other words these two are equivalent:
    #   Node(val1, left=n2, right=n3)
    #   Node(val2, right=n3, left=n2)
    #
    # n2 and n3 are sub-trees.
    #
    # This makes this problem context-sensitive - the relevant context sensitive grammar:
    #   G = (N, Sigma, P, S)
    #
    # Where:
    #   N = {S, N, L, R, O, P}
    #   Sigma = {a, n, m}
    #   P = {
    #     S   -> N,
    #     N   -> aLR,
    #     N   -> aRL,
    #     L   -> N | e,
    #     R   -> N | e,
    #     aRe -> O,
    #     aLe -> P,
    #     Oa  -> n,
    #     Pa  -> m,
    #   }
    #
    # Chars m and n represent constructed nodes, a is on input and can be seen as "Node(val, " (start of a node
    #  definition) and e represents epsilon from CSG theory.
    # Now we can construct an equivalent a pushdown automation that accepts the given grammar.
    #
    # TODO: implement - this is now automated task


if __name__ == '__main__':
    test_node = Node('root', Node('left', Node('left.left')), Node('right'))
    # assert deserialize(serialize(test_node)).left.left.val == 'left.left'
