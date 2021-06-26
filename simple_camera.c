  R = VecSet(VG4_RndMatrView.A[0][0], VG4_RndMatrView.A[1][0], VG4_RndMatrView.A[2][0]);
  D = VecSet(-VG4_RndMatrView.A[0][2], -VG4_RndMatrView.A[1][2], -VG4_RndMatrView.A[2][2]);
  D.Y = 0;
  D = VecNormalize(D);

  Uni->CamDist += Ani->GlobalDeltaTime * (0.2 * Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 26) * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
  Uni->RotY += Ani->GlobalDeltaTime * (-0.8 * 30 * Ani->Keys[VK_LBUTTON] * Ani->Mdx + 3 * 0.47 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));
  Uni->RotX += Ani->GlobalDeltaTime * (-0.8 * 30 * Ani->Keys[VK_LBUTTON] * Ani->Mdy + 0.47 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

  Uni->At = VecAddVec(Uni->At, VecMulNum(R, (Ani->Keys['D'] - Ani->Keys['A']) * 18 * Ani->GlobalDeltaTime));
  Uni->At = VecAddVec(Uni->At, VecMulNum(D, (Ani->Keys['W'] - Ani->Keys['S']) * 18 * Ani->GlobalDeltaTime));

  VG4_RndCamSet(PointTransform(VecSet(0, 0, Uni->CamDist),
                               MatrMulMatr3(MatrRotateX(-18 * 5 / 2.0 * Uni->RotX),
                                            MatrRotateY(-102 * 5 / 8.0 * Uni->RotY),
                                            MatrTranslate(Uni->At))),
    Uni->At, VecSet(0, 1, 0));
