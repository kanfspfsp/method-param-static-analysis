//===--- MoreThanThreeParametersCheck.cpp - clang-tidy --------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MoreThanThreeParametersCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misc {

void MoreThanThreeParametersCheck::registerMatchers(MatchFinder *Finder) {
    Finder->addMatcher(cxxMethodDecl().bind("method"), this);
}

void MoreThanThreeParametersCheck::check(const MatchFinder::MatchResult &Result) {
    const auto method = Result.Nodes.getNodeAs<CXXMethodDecl>("method");
    const auto params = method->getNumParams ();
    
    if (params>3) {
        diag(method->getLocation(), "Method has more than 3 Parameters");
    }
}

} // namespace misc
} // namespace tidy
} // namespace clang
