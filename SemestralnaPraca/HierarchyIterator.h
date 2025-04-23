#pragma once

#include "TerritorialUnit.h"
#include <libds/adt/tree.h>
#include <iostream>
#include <string>

class HierarchyIterator {
public:
    using Tree = ds::adt::MultiwayTree<TerritorialUnit>;
    using Node = Tree::Node;

    HierarchyIterator(Tree* tree)
        : tree_(tree), current_(tree->accessRoot()) {
    }

    void moveToParent() {
        Node* parent = tree_->accessParent(*current_);
        if (parent != nullptr) {
            current_ = parent;
        }
        else {
            std::cout << "Already at root, cannot move up.\n";
        }
    }

    void moveToChild(size_t index) {
        if (tree_->hasNThSon(*current_, index)) {
            current_ = tree_->accessSon(*current_, index);
        }
        else {
            std::cout << "Invalid child index.\n";
        }
    }

    void printCurrent() const {
        if (current_) {
            const auto& unit = current_->data_;
            std::cout << "Aktuálny vrchol: " << unit.getName()
                << " (" << unit.getType();
        }
    }

    void printChildren() const {
        size_t count = tree_->degree(*current_);
        std::cout << "Deti aktuálneho vrcholu:\n";
        for (size_t i = 0; i < count; ++i) {
            const auto* child = tree_->accessSon(*current_, i);
            const auto& unit = child->data_;
            std::cout << "  " << i << ": " << unit.getName() << " (" << unit.getType() << ")\n";
        }
    }

    void applyPredicateToDescendants(const std::function<bool(const TerritorialUnit&)>& pred) const {
        std::function<void(Node*)> recurse;
        recurse = [&](Node* node) {
            if (pred(node->data_)) {
                std::cout << "- " << node->data_.getName() << "\n";
            }

            size_t children = tree_->degree(*node);
            for (size_t i = 0; i < children; ++i) {
                Node* child = tree_->accessSon(*node, i);
                recurse(child);
            }
            };

        recurse(current_);
    }

    Node* getCurrent() const {
        return current_;
    }

private:
    Tree* tree_;
    Node* current_;
};
