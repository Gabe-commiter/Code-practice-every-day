// file name ComplexList.h
// Created by Gabe with CLion.
// 2020/3/12 11:50


#ifndef COMPLEXLIST_H
#define COMPLEXLIST_H

#pragma once

struct ComplexListNode
{
    int                 m_nValue;
    ComplexListNode*    m_pNext;
    ComplexListNode*    m_pSibling;
};

ComplexListNode* CreateNode(int nValue);
void BuildNodes(ComplexListNode* pNode, ComplexListNode* pNext, ComplexListNode* pSibling);
void PrintList(ComplexListNode* pHead);
#endif //COMPLEXLIST_H
