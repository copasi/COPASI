// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Main
//
// (C) Stefan Hoops 2002
//

#define COPASI_MAIN
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>

#include "copasi/copasi.h"

#include "copasi/function/CEvaluationTree.h"
#include "copasi/function/CEvaluationNode.h"
//#include "copasi/function/CEvaluationNodeOperator.h"
//#include "copasi/function/CEvaluationNodeFunction.h"
//#include "copasi/function/CEvaluationNode.h"

#include "CNormalTranslation.h"

//#include <vector>
#include "copasi/core/CDataContainer.h"

#include "copasi/utilities/CopasiTime.h"
#include "copasi/randomGenerator/CRandom.h"
#include "copasi/report/CKeyFactory.h"

#include "copasi/function/CFunction.h"

/*
tested functions:

Allosteric Inhibition:

V*substrate*(Ks+substrate)^(n-1)/(L*(Ks*(1+Inhibitor/Ki))^n+(Ks+substrate)^n)
same as:
(Ks+substrate)^(-1)*(substrate*V)/(1+L*((Ki^(-1)*Ks*Inhibitor+Ks)/(substrate+Ks))^n))
simplified form:
(V * substrate * ((Ks + substrate)^n) * (Ki^n))/(Ks * L * ((Inhibitor * Ks + Ki * Ks)^n) + Ks * ((Ks + substrate)^n) * (Ki^n) + L * substrate * ((Inhibitor * Ks + Ki * Ks)^n) + substrate * ((Ks + substrate)^n) * (Ki^n))

Hyperbolic Modifier:

((Vf*substrate/Kms-Vr*product/Kmp)*(1+b*Modifier/(a*Kd)))/(1+Modifier/Kd+(substrate/Kms+product/Kmp)*(1+Modifier/(a*Kd)))
same as:
(Kms^(-1)*Vf*substrate-Kmp^(-1)*Vr*product+((Vf*b*substrate)/(Kms*a)+(b*(-Vr)*product)/(a*Kmp))*Modifier/Kd)/(1+1/Kmp*product+1/Kms*substrate+(1+1/(a*Kms)*substrate+1/(a*Kmp)*product)*Modifier/Kd)
simplified form:
(Kd * Kmp * Vf * a * substrate + (-1) * Kd * Kms * Vr * a * product + Kmp * Modifier * Vf * b * substrate + (-1) * Kms * Modifier * Vr * b * product)/(Kd * Kmp * Kms * a + Kd * Kmp * a * substrate + Kd * Kms * a * product + Kmp * Kms * Modifier * a + Kmp * Modifier * substrate + Kms * Modifier * product)

Substrate Activation:

V*(substrate/Ksa)^2/(1+substrate/Ksc+substrate/Ksa+(substrate/Ksa)^2)
same as:
V*substrate^2/(substrate^2+Ksa*(Ksa*Ksc^(-1)+1)*substrate+Ksa^2)
simplified form:
(Ksc * V * substrate^2)/(Ksa^2 * Ksc + Ksa^2 * substrate + Ksa * Ksc * substrate + Ksc * substrate^2)

Specific Activation rev.:

(Vf*substrate/Kms-Vr*product/Kmp)*Activator/(Ka+(1+substrate/Kms+product/Kmp)*Activator)
same as:
(Kmp*Vf*substrate-Kms*Vr*product)/(Activator^(-1)*Ka*Kms*Kmp+Kms*Kmp+Kmp*substrate+Kms*product)
simplified form:
(Activator * Kmp * Vf * substrate + (-1) * Activator * Kms * Vr * product)/(Activator * Kmp * Kms + Activator * Kmp * substrate + Activator * Kms * product + Ka * Kmp * Kms)

Ordered Bi Bi:

Vf*(substratea*substrateb-productp*productq/Keq)/(substratea*substrateb*(1+productp/Kip)+Kma*substrateb+Kmb*(substratea+Kia)+Vf/(Vr*Keq)*(Kmq*productp*(1+substratea/Kia)+productq*(Kmp*(1+Kia*substrateb/(Kma*Kmb))+productp*(1+substrateb/Kib))))
same as:
Vf*(productp^(-1)*productq^(-1)-substratea^(-1)*substrateb^(-1)*Keq^(-1))/(productq^(-1)*(productp^(-1)+Kip^(-1))+Kma*substratea^(-1)*productp^(-1)*productq^(-1)+productp^(-1)*productq^(-1)*Kmb*substrateb^(-1)*(1+Kia*substratea^(-1))+Vf/(Vr*Keq)*(Kmq*productq^(-1)*substrateb^(-1)*(substratea^(-1)+1/Kia)+Kmp*productp^(-1)*substratea^(-1)*(substrateb^(-1)+Kia/(Kma*Kmb))+substratea^(-1)*(substrateb^(-1)+1/Kib)))
simplified form:
(Keq * Kia * Kib * Kip * Kma * Kmb * Vf * Vr * substratea * substrateb + (-1) * Kia * Kib * Kip * Kma * Kmb * Vf * Vr * productp * productq)/(Keq * Kia^2 * Kib * Kip * Kma * Kmb^2 * Vr + Keq * Kia * Kib * Kip * Kma^2 * Kmb * Vr * substrateb + Keq * Kia * Kib * Kip * Kma * Kmb^2 * Vr * substratea + Keq * Kia * Kib * Kip * Kma * Kmb * Vr * substratea * substrateb + Keq * Kia * Kib * Kma * Kmb * Vr * productp * substratea * substrateb + Kia^2 * Kib * Kip * Kmp * Vf * productq * substrateb + Kia * Kib * Kip * Kma * Kmb * Kmp * Vf * productq + Kia * Kib * Kip * Kma * Kmb * Kmq * Vf * productp + Kia * Kib * Kip * Kma * Kmb * Vf * productp * productq + Kia * Kip * Kma * Kmb * Vf * productp * productq * substrateb + Kib * Kip * Kma * Kmb * Kmq * Vf * productp * substratea)

Reversible Hill:

Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/(1+(substrate/Shalve+product/Phalve)^h)
same as:
(substrate*Phalve+product*Shalve)^(h-1)*Vf/Shalve*(substrate-Keq^(-1)*product)/(Phalve^(h-1)*Shalve^(h-1)+(substrate*Phalve+product*Shalve)^h/(Shalve*Phalve))
same as:
 Phalve*Shalve*(substrate*Phalve+product*Shalve)^(h-1)*Shalve^(-1)*Vf*(substrate-Keq^(-1)*product)/(Phalve^h*Shalve^h+(substrate*Phalve+product*Shalve)^h)
simplified form:
(Keq * Phalve * Vf * substrate * ((Phalve * substrate + Shalve * product)^h) + (-1) * Phalve * Vf * product * ((Phalve * substrate + Shalve * product)^h))/(Keq * Phalve * substrate * ((Phalve * substrate + Shalve * product)^h) + Keq * Phalve * substrate * (Phalve^h) * (Shalve^h) + Keq * Shalve * product * ((Phalve * substrate + Shalve * product)^h) + Keq * Shalve * product * (Phalve^h) * (Shalve^h))

Reversible Hill 1 Modifier:

Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(Modifier/Mhalve)^h)/(1+alpha*(Modifier/Mhalve)^h)+(substrate/Shalve+product/Phalve)^h)
same as:
(Vf*Shalve^(-1)*(substrate-Keq^(-1)*product)*(Shalve^(-1)*substrate+Phalve^(-1)*product)^(h-1))/((Modifier^h+Mhalve^h)/(alpha*Modifier^h+Mhalve^h)+(Shalve^(-1)*substrate+Phalve^(-1)*product)^h)
simplified form:
(Keq * Phalve * Vf * alpha^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (Modifier^(2 * h)) + 2 * Keq * Phalve * Vf * alpha * substrate * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^h) * (Modifier^h) + Keq * Phalve * Vf * substrate * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^(2 * h)) + (-1) * Phalve * Vf * alpha^2 * product * ((Phalve * substrate + Shalve * product)^h) * (Modifier^(2 * h)) + (-2) * Phalve * Vf * alpha * product * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^h) * (Modifier^h) + (-1) * Phalve * Vf * product * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^(2 * h)))/(Keq * Phalve * alpha^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (Modifier^(2 * h)) + 2 * Keq * Phalve * alpha * substrate * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^h) * (Modifier^h) + Keq * Phalve * alpha * substrate * (Mhalve^h) * (Modifier^h) * (Phalve^h) * (Shalve^h) + Keq * Phalve * alpha * substrate * (Modifier^(2 * h)) * (Phalve^h) * (Shalve^h) + Keq * Phalve * substrate * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^(2 * h)) + Keq * Phalve * substrate * (Mhalve^(2 * h)) * (Phalve^h) * (Shalve^h) + Keq * Phalve * substrate * (Mhalve^h) * (Modifier^h) * (Phalve^h) * (Shalve^h) + Keq * Shalve * alpha^2 * product * ((Phalve * substrate + Shalve * product)^h) * (Modifier^(2 * h)) + 2 * Keq * Shalve * alpha * product * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^h) * (Modifier^h) + Keq * Shalve * alpha * product * (Mhalve^h) * (Modifier^h) * (Phalve^h) * (Shalve^h) + Keq * Shalve * alpha * product * (Modifier^(2 * h)) * (Phalve^h) * (Shalve^h) + Keq * Shalve * product * ((Phalve * substrate + Shalve * product)^h) * (Mhalve^(2 * h)) + Keq * Shalve * product * (Mhalve^(2 * h)) * (Phalve^h) * (Shalve^h) + Keq * Shalve * product * (Mhalve^h) * (Modifier^h) * (Phalve^h) * (Shalve^h))

Reversible Hill 2 modifiers:

Vf*substrate/Shalve*(1-product/(substrate*Keq))*(substrate/Shalve+product/Phalve)^(h-1)/((1+(ModifierA/MAhalve)^h+(ModifierB/MBhalve)^h)/(1+alphaA*(ModifierA/MAhalve)^h+alphaB*(ModifierB/MBhalve)^h+alphaA*alphaB*alphaAB*(ModifierA/MAhalve)^h*(ModifierB/MBhalve)^h)+(substrate/Shalve+product/Phalve)^h)
same as:
Shalve^(-1)*Vf*(substrate-Keq^(-1)*product)*(Shalve^(-1)*substrate+Phalve^(-1)*product)^(h-1)/((MAhalve^h*MBhalve^h+ModifierA^h*MBhalve^h+ModifierB^h*MAhalve^h)/(MAhalve^h*MBhalve^h+alphaA*ModifierA^h*MBhalve^h+alphaB*ModifierB^h*MAhalve^h+alphaA*alphaB*alphaAB*ModifierA^h*ModifierB^h)+(Shalve^(-1)*substrate+Phalve^(-1)*product)^h)
simplified form:
 (Keq * Phalve * Vf * alphaA^2 * alphaAB^2 * alphaB^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (ModifierA^(2 * h)) * (ModifierB^(2 * h)) + 2 * Keq * Phalve * Vf * alphaA^2 * alphaAB * alphaB * substrate * ((Phalve * substrate + Shalve * product)^h) * (MBhalve^h) * (ModifierA^(2 * h)) * (ModifierB^h) + Keq * Phalve * Vf * alphaA^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (MBhalve^(2 * h)) * (ModifierA^(2 * h)) + 2 * Keq * Phalve * Vf * alphaA * alphaAB * alphaB^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^h) * (ModifierA^h) * (ModifierB^(2 * h)) + 2 * Keq * Phalve * Vf * alphaA * alphaAB * alphaB * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^h) * (MBhalve^h) * (ModifierA^h) * (ModifierB^h) + 2 * Keq * Phalve * Vf * alphaA * alphaB * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^h) * (MBhalve^h) * (ModifierA^h) * (ModifierB^h) + 2 * Keq * Phalve * Vf * alphaA * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^h) * (MBhalve^(2 * h)) * (ModifierA^h) + Keq * Phalve * Vf * alphaB^2 * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^(2 * h)) * (ModifierB^(2 * h)) + 2 * Keq * Phalve * Vf * alphaB * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^(2 * h)) * (MBhalve^h) * (ModifierB^h) + Keq * Phalve * Vf * substrate * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^(2 * h)) * (MBhalve^(2 * h)) + (-1) * Phalve * Vf * alphaA^2 * alphaAB^2 * alphaB^2 * product * ((Phalve * substrate + Shalve * product)^h) * (ModifierA^(2 * h)) * (ModifierB^(2 * h)) + (-2) * Phalve * Vf * alphaA^2 * alphaAB * alphaB * product * ((Phalve * substrate + Shalve * product)^h) * (MBhalve^h) * (ModifierA^(2 * h)) * (ModifierB^h) + (-1) * Phalve * Vf * alphaA^2 * product * ((Phalve * substrate + Shalve * product)^h) * (MBhalve^(2 * h)) * (ModifierA^(2 * h)) + (-2) * Phalve * Vf * alphaA * alphaAB * alphaB^2 * product * ((Phalve * substrate + Shalve * product)^h) * (MAhalve^h) * (Mo
 */
