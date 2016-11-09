/*
 * ParseTree.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>

ParseTree::ParseTree() {
	prog = getRoot();

}

Node ParseTree::getRoot() {
	if (prog == NULL) {
		prog = new Node(RuleType::PROG);
		Node decls = new Node(RuleType::DECLS);
		Node stmts = new Node(RuleType::STATEMENTS);
		prog.add_Note(decls);
		prog.add_Note(stmts);
	}
	return prog;
}


