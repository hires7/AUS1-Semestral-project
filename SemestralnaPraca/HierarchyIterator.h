#pragma once

#include "TerritorialUnit.h"
#include <libds/adt/tree.h>
#include <iostream>

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
                << " (" << unit.getType() << " )";
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

    ds::adt::ImplicitList<TerritorialUnit*>* applyPredicateToDescendants(const std::function<bool(const TerritorialUnit&)>& predicate) {
        auto* results  = new ds::adt::ImplicitList<TerritorialUnit*>;

        std::function<void(Node*)> recurse = [&](Node* node) {
            if (predicate(node->data_)) {
                results->insertLast(&node->data_);  // Changed from push_back
            }

            size_t childCount = tree_->degree(*node);
            for (size_t i = 0; i < childCount; ++i) {
                recurse(tree_->accessSon(*node, i));
            }
            };

        recurse(current_);
        return results;
    }


    Node* getCurrent() const {
        return current_;
    }

    void printPopulationByYear() const {
        if (current_) {
            int year;
            std::cout << "Zadaj rok (2020-2024): ";
            std::cin >> year;

            if (year < 2020 || year > 2024) {
                std::cout << "Neplatný rok.\n";
                return;
            }

            const TerritorialUnit& unit = current_->data_;
            std::cout << "Populácia pre '" << unit.getName() << "' v roku " << year
                << ": " << unit.getPopulation(year) << "\n";
        }
    }


private:
    Tree* tree_;
    Node* current_;
};
