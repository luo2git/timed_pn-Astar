#pragma once

extern CrossList SMatrix_C;
extern CrossList SMatrix_C_pre;
void CreateNode(Tree *Tr, int Transition, int Delay[], int new_m[], int new_m_x[], int new_m_g);
void CreateAstarNode(AstarTree *Tr, int Transition, int Delay[], int new_m[], int new_m_x[], int new_m_g);