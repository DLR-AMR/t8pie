/*
  This file is part of t8pie.

  Copyright (C) 2025 the developers

  t8pie is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.

  t8pie is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with t8pie; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

/* This file is modified from the t8code file test/t8_gtest_vtk_linkage.cxx as of November 2025 */

/* In this test we create a vtk unstructured Grid object and check whether
 * vtk version T8PIE was configured to link with is the version that is actually
 * linked.
 * The purpose of this test is to check whether t8pie successfully links
 * against vtk.
 * If t8pie was not configured with --enable-vtk then this test
 * does nothing and is always passed.
 */
#include <iostream>
#include <gtest/gtest.h>
#if T8PIE_ENABLE_VTK
#include <vtkUnstructuredGrid.h>
#include <vtkNew.h>
#endif

/* Check whether T8PIE_VTK_VERSION_USED equals VTK_MAJOR_VERSION.VTK_MINOR_VERSION */
TEST (t8pie_gtest_vtk_linkage, t8pie_test_vtk_version_number)
{
#if T8PIE_ENABLE_VTK
  char vtk_version[BUFSIZ];
  snprintf (vtk_version, BUFSIZ, "%i.%i", VTK_MAJOR_VERSION, VTK_MINOR_VERSION);
  EXPECT_FALSE (strcmp (T8PIE_VTK_VERSION_USED, vtk_version))
    << "linked vtk version (" << vtk_version << ") does not equal the version t8pie was configured with ("
    << T8PIE_VTK_VERSION_USED << ").\n";
  if (!strcmp (T8PIE_VTK_VERSION_USED, vtk_version)) {
    std::cout << "Using vtk version " << vtk_version << std::endl;
  }
#endif
}

/* Check whether T8PIE_VTK_VERSION_USED equals T8_VTK_VERSION_USED */
TEST (t8pie_gtest_vtk_linkage, t8pie_and_t8code_use_same_vtk_version)
{
#if T8PIE_ENABLE_VTK
  EXPECT_FALSE (strcmp (T8PIE_VTK_VERSION_USED, T8_VTK_VERSION_USED))
    << "linked vtk version (" << T8PIE_VTK_VERSION_USED << ") does not equal the version t8code was configured with ("
    << T8_VTK_VERSION_USED << ").\n";
#endif
}

TEST (t8pie_gtest_vtk_linkage, t8pie_uses_vtk_if_t8code_does)
{
  #if T8_ENABLE_VTK
    #if !T8PIE_ENABLE_VTK
      ASSERT_FALSE (true) << "t8code was linked against VTK but t8pie was not.";
    #endif
  #endif  
}

/* Check whether we can successfully execute VTK code */
TEST (t8pie_gtest_vtk_linkage, t8pie_test_vtk_linkage)
{
#if T8PIE_ENABLE_VTK
  vtkNew<vtkUnstructuredGrid> unstructuredGrid;

  std::cout << ("Successfully created VTK unstructuredGrid object.\n");
#else
  std::cout << ("This version of t8pie is not compiled with vtk support.\n");
#endif
}
