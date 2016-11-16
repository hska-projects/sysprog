/*
 * ParseTree.cpp
 *
 *  Created on: 02.11.2016
 *      Author: dominik
 */

#include <cstddef>

ParseTree::ParseTree() {
	this->prog = getRoot();
}

Node* ParseTree::getRoot() {
	if (this->prog == NULL) {
		this->prog = new Node(RuleType::PROG);
		Node* decls = new Node(RuleType::DECLS);
		Node* stmts = new Node(RuleType::STATEMENTS);
		prog->add_ChildNode(decls);
		prog->add_ChildNode(stmts);
	}
	return prog;
}
