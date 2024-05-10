// cmdGTest.cpp : command file
//

#include "stdafx.h"
#include "GTestPlugIn.h"
#include "RhinoSdkCommand.h"
#include <iostream>  // This header includes std::cerr and std::endl

////////////////////////////////////////////////////////////////
//
// BEGIN GTest command
//

#pragma region GTest command

// Do NOT put the definition of class CCommandGTest in a header
// file. There is only ONE instance of a CCommandGTest class
// and that instance is the static theGTestCommand that appears
// immediately below the class definition.

class CCommandGTest : public CRhinoCommand
{
public:
  // The one and only instance of CCommandGTest is created below.
  // No copy constructor or operator= is required.
  // Values of member variables persist for the duration of the application.

  // CCommandGTest::CCommandGTest()
  // is called exactly once when static theGTestCommand is created.
  CCommandGTest() = default;

  // CCommandGTest::~CCommandGTest()
  // is called exactly once when static theGTestCommand is destroyed.
  // The destructor should not make any calls to the Rhino SDK. 
  // If your command has persistent settings, then override 
  // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
  ~CCommandGTest() = default;

  // Returns a unique UUID for this command.
  // If you try to use an id that is already being used, then
  // your command will not work. Use GUIDGEN.EXE to make unique UUID.
  UUID CommandUUID() override
  {
    // {D55BBBB5-2DE2-4689-8D1C-DAE6F6B1E085}
    static const GUID GTestCommand_UUID = 
    {0xd55bbbb5,0x2de2,0x4689,{0x8d,0x1c,0xda,0xe6,0xf6,0xb1,0xe0,0x85}};
    return GTestCommand_UUID;
  }

  // Returns the English command name.
  // If you want to provide a localized command name, then override 
  // CRhinoCommand::LocalCommandName.
  const wchar_t* EnglishCommandName() override { return L"GTestRuledSurface"; }

  // Rhino calls RunCommand to run the command.
  CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGTest object
// Do NOT create any other instance of a CCommandGTest class.
static class CCommandGTest theGTestCommand;

CRhinoCommand::result CCommandGTest::RunCommand(const CRhinoCommandContext& context)
{
        // CCommandRuleSurface::RunCommand() is called when the user
        // runs the "RuleSurface".

        // TODO: Add command code here.

        // Prompt the user to select two curves
        CRhinoGetObject go;
        go.SetCommandPrompt(L"Select two curves");
        go.SetGeometryFilter(ON::curve_object);
        go.GetObjects(2, 2); // Prompt for exactly 2 curves

        if (go.CommandResult() == CRhinoCommand::success)
        {
            const ON_Curve* curveA = go.Object(0).Curve();
            const ON_Curve* curveB = go.Object(1).Curve();

            if (curveA && curveB)
            {
                RhinoApp().Print(L"Selected curves:\n");

                //Create the Ruled Surf

             // Add the surface to the document
             // Create the ruled surface
                ON_NurbsSurface ruledSurface;
                if (ruledSurface.CreateRuledSurface(*curveA, *curveB))
                {
                    // Convert ON_NurbsSurface to ON_Surface
                    ON_Surface* surface = ruledSurface.DuplicateSurface();
                    if (!surface)
                    {
                        RhinoApp().Print(L"Failed to convert ruled surface.\n");
                        return CRhinoCommand::failure;
                    }

                    // Add the surface to the document
                    CRhinoSurfaceObject* surfaceObj = new CRhinoSurfaceObject();
                    surfaceObj->SetSurface(surface);
                    if (context.m_doc.AddObject(surfaceObj))
                    {
                        // Success message
                        RhinoApp().Print(L"Ruled surface created and added to the document.\n");
                        context.m_doc.Redraw();
                        return CRhinoCommand::success;
                    }
                    else
                    {
                        // Error adding the surface
                        delete surfaceObj;
                    }
                }
            }
            else
            {
                RhinoApp().Print(L"Failed to select 2 curves.\n");
                return CRhinoCommand::failure;
            }

        }

        return CRhinoCommand::success;
}

#pragma endregion

////////////////////////////////////////////////////////////////
//
// BEGIN GTest2 command
//

#pragma region GTest2 command

// Do NOT put the definition of class CCommandGTest2 in a header
// file. There is only ONE instance of a CCommandGTest2 class
// and that instance is the static theGTestCommand that appears
// immediately below the class definition.

class CCommandGTest2 : public CRhinoCommand
{
public:
    // The one and only instance of CCommandGTest2 is created below.
    // No copy constructor or operator= is required.
    // Values of member variables persist for the duration of the application.

    // CCommandGTest2::CCommandGTest2()
    // is called exactly once when static theGTestCommand is created.
    CCommandGTest2() = default;

    // CCommandGTest2::~CCommandGTest2()
    // is called exactly once when static theGTestCommand is destroyed.
    // The destructor should not make any calls to the Rhino SDK. 
    // If your command has persistent settings, then override 
    // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
    ~CCommandGTest2() = default;

    // Returns a unique UUID for this command.
    // If you try to use an id that is already being used, then
    // your command will not work. Use GUIDGEN.EXE to make unique UUID.
    UUID CommandUUID() override
    {
        // {D55BBBB5-2DE2-4689-8D1C-DAE6F6B1E085}
        static const GUID GTest2Command_UUID =
        { // {12345678-1234-5678-1234-567812345678}
        0x12345678, 0x1234, 0x5678, { 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78 } };
        return GTest2Command_UUID;
    }

    // Returns the English command name.
    // If you want to provide a localized command name, then override 
    // CRhinoCommand::LocalCommandName.
    const wchar_t* EnglishCommandName() override { return L"GTestLoftedSurface"; }

    // Rhino calls RunCommand to run the command.
    CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGTest2 object
// Do NOT create any other instance of a CCommandGTest2 class.
static class CCommandGTest2 theGTest2Command;

CRhinoCommand::result CCommandGTest2::RunCommand(const CRhinoCommandContext& context)
{
	// Prompt the user to select curves
	CRhinoGetObject go;
	go.SetCommandPrompt(L"Select curves for lofting");
	go.SetGeometryFilter(ON::curve_object);
	go.EnableSubObjectSelect(FALSE);
	go.GetObjects(2, 0); // Prompt for at least 2 curves

	if (go.CommandResult() == CRhinoCommand::success)
	{
		ON_SimpleArray<const ON_Curve*> selectedCurves;
		for (int i = 0; i < go.ObjectCount(); ++i)
		{
			const ON_Curve* curve = go.Object(i).Curve();
			if (curve)
				selectedCurves.Append(curve);
		}

		if (selectedCurves.Count() >= 2)
		{
			// Create a loft surface.
			ON_Surface* surface = ON_Surface::CreateCubicLoft(selectedCurves.Count(), selectedCurves, 1.0);

			if (surface != nullptr)
			{
				// Add the surface to the document
				CRhinoSurfaceObject* surfaceObj = new CRhinoSurfaceObject();
				surfaceObj->SetSurface(surface);
				if (context.m_doc.AddObject(surfaceObj))
				{
					// Success message
					RhinoApp().Print(L"Loft surface created and added to the document.\n");
					context.m_doc.Redraw();
					return CRhinoCommand::success;
				}
				else
				{
					// Error adding the surface
					delete surfaceObj;
				}
			}
			else
			{
				RhinoApp().Print(L"Failed to create Cubic lofted surface.\n");
			}
		}
	}

	RhinoApp().Print(L"Failed to create lofted surface.\n");
	return CRhinoCommand::failure;
}
#pragma endregion

////////////////////////////////////////////////////////////////
//
// BEGIN GTest3 command
//

#pragma region GTest3 command

// Do NOT put the definition of class CCommandGTest3 in a header
// file. There is only ONE instance of a CCommandGTest3 class
// and that instance is the static theGTestCommand that appears
// immediately below the class definition.

class CCommandGTest3 : public CRhinoCommand
{
public:
    // The one and only instance of CCommandGTest3 is created below.
    // No copy constructor or operator= is required.
    // Values of member variables persist for the duration of the application.

    // CCommandGTest3::CCommandGTest3()
    // is called exactly once when static theGTestCommand is created.
    CCommandGTest3() = default;

    // CCommandGTest3::~CCommandGTest3()
    // is called exactly once when static theGTestCommand is destroyed.
    // The destructor should not make any calls to the Rhino SDK. 
    // If your command has persistent settings, then override 
    // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
    ~CCommandGTest3() = default;

    // Returns a unique UUID for this command.
    // If you try to use an id that is already being used, then
    // your command will not work. Use GUIDGEN.EXE to make unique UUID.
    UUID CommandUUID() override
    {
        // {D55BBBB5-2DE2-4689-8D1C-DAE6F6B1E085}
        static const GUID GTest2Command_UUID =
        { 0x6c408196,0xf7b8,0x43f5,{0x80,0x0a,0xc2,0x2a,0x27,0x18,0xc8,0xc2} };
        
        return GTest2Command_UUID;
    }

    // Returns the English command name.
    // If you want to provide a localized command name, then override 
    // CRhinoCommand::LocalCommandName.
    const wchar_t* EnglishCommandName() override { return L"GTestOffset"; }

    // Rhino calls RunCommand to run the command.
    CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGTest3 object
// Do NOT create any other instance of a CCommandGTest3 class.
static class CCommandGTest3 theGTest3Command;


// Function to create an offset surface
ON_Surface* CreateOffsetSurface(const ON_Surface* inputSurface, double offsetDistance)
{
    if (inputSurface == nullptr)
    {
        // Handle null input
        std::cerr << "Input surface is null." << std::endl;
        return nullptr;
    }

    // Clone the input surface to ensure the original is not modified
    ON_Surface* clonedSurface = inputSurface->DuplicateSurface();
    if (clonedSurface == nullptr)
    {
        std::cerr << "Failed to duplicate the input surface." << std::endl;
        return nullptr;
    }

    // Attempt to create an offset surface
    ON_Surface* offsetSurface = clonedSurface->Offset(offsetDistance, 0.01 /* tolerance */, false /* loose offset */);
    if (offsetSurface == nullptr)
    {
        std::cerr << "Failed to create an offset surface." << std::endl;
        delete clonedSurface; // Clean up
        return nullptr;
    }

    // Return the newly created offset surface
    return offsetSurface;
}

CRhinoCommand::result GetOffsetDistance(double& offset_distance)
{
    CRhinoGetNumber gn;
    gn.SetCommandPrompt(L"Enter the offset distance");
    gn.SetLowerLimit(0, FALSE); // Optional: Set a lower limit for the distance, not strictly enforced
    gn.GetNumber();
    if (gn.CommandResult() != CRhinoCommand::success)
        return gn.CommandResult();

    offset_distance = gn.Number();
    return CRhinoCommand::success;
}

CRhinoCommand::result CCommandGTest3::RunCommand(const CRhinoCommandContext& context)
{
    // Prompt the user to select a NurbsSurface object
    CRhinoGetObject go2;
    go2.SetCommandPrompt(L"Select a NurbsSurface");
    go2.SetGeometryFilter(CRhinoGetObject::surface_object | CRhinoGetObject::polysrf_object);
    go2.EnableSubObjectSelect(FALSE);
    go2.GetObjects(1, 1); // Get exactly one object
    if (go2.CommandResult() == CRhinoCommand::success)
    {
         const CRhinoObjRef& obj_ref = go2.Object(0);
        const ON_Surface* surface = obj_ref.Surface();
        if (!surface)
            return CRhinoCommand::failure;
 
        //Prumpt for distance
        double offset_distance=1.0;
        CRhinoCommand::result res = GetOffsetDistance(offset_distance);
        if (res != CRhinoCommand::success)
            return res;

        ON_Surface* offsetSrf = CreateOffsetSurface(surface, offset_distance);
        if (offsetSrf != nullptr)
        {
            // Add the surface to the document
            CRhinoSurfaceObject* surfaceObj = new CRhinoSurfaceObject();

            surfaceObj->SetSurface(offsetSrf);
            if (context.m_doc.AddObject(surfaceObj))
            {
                // Success message
                RhinoApp().Print(L"Offset Surface created and added to the document.\n");
                context.m_doc.Redraw();
                return CRhinoCommand::success;
            }
            else
            {
                // Error adding the surface
                delete surfaceObj;
            }
        }
        else
        {
            RhinoApp().Print(L"Failed to create Offset Surface.\n");
        }
    }   
    return CRhinoCommand::success;
}
#pragma endregion


//Command 4 Srf-Srf-Distance

#pragma region GTest4 command

// Do NOT put the definition of class CCommandGTest4 in a header
// file. There is only ONE instance of a CCommandGTest4 class
// and that instance is the static theGTestCommand that appears
// immediately below the class definition.

class CCommandGTest4 : public CRhinoCommand
{
public:
    // The one and only instance of CCommandGTest4 is created below.
    // No copy constructor or operator= is required.
    // Values of member variables persist for the duration of the application.

    // CCommandGTest4::CCommandGTest4()
    // is called exactly once when static theGTestCommand is created.
    CCommandGTest4() = default;

    // CCommandGTest4::~CCommandGTest4()
    // is called exactly once when static theGTestCommand is destroyed.
    // The destructor should not make any calls to the Rhino SDK. 
    // If your command has persistent settings, then override 
    // CRhinoCommand::SaveProfile and CRhinoCommand::LoadProfile.
    ~CCommandGTest4() = default;

    // Returns a unique UUID for this command.
    // If you try to use an id that is already being used, then
    // your command will not work. Use GUIDGEN.EXE to make unique UUID.
    UUID CommandUUID() override
    {
        // {D55BBBB5-2DE2-4689-8D1C-DAE6F6B1E085}
        static const GUID GTest2Command_UUID =
        { 0x12345678, 0x9abc, 0xdef0, { 0x12, 0x34, 0x56, 0x78, 0x9a, 0xbc, 0xde, 0xf0 } };

        return GTest2Command_UUID;
    }

    // Returns the English command name.
    // If you want to provide a localized command name, then override 
    // CRhinoCommand::LocalCommandName.
    const wchar_t* EnglishCommandName() override { return L"GTestSrfDistance"; }

    // Rhino calls RunCommand to run the command.
    CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandGTest4 object
// Do NOT create any other instance of a CCommandGTest4 class.
static class CCommandGTest4 theGTest4Command;



CRhinoCommand::result CCommandGTest4::RunCommand(const CRhinoCommandContext& context)
{
    CRhinoGetObject go;
    go.SetCommandPrompt(L"Select two surfaces");
    go.SetGeometryFilter(CRhinoGetObject::surface_object);
    go.GetObjects(2, 2);
    if (go.CommandResult() != CRhinoCommand::success)
        return go.CommandResult();

    const CRhinoObjRef& refA = go.Object(0);
    const CRhinoObjRef& refB = go.Object(1);
    const ON_Surface* surface1 = refA.Surface();
    const ON_Surface* surface2 = refB.Surface();

    if (!surface1 || !surface2)
        return CRhinoCommand::failure;

   
// Prompt for grid size
    CRhinoGetString gs;
    gs.SetCommandPrompt(L"Enter grid size (10-1000)");
    gs.SetDefaultString(L"100");
    gs.AcceptNothing(TRUE);
    gs.GetString();
    if (gs.CommandResult() != CRhinoCommand::success)
        return gs.CommandResult();

    int gridSize;
    if (gs.Number() == 0 && gs.String() != nullptr && wcscmp(gs.String(), L"") == 0)
    {
        gridSize = 100;
    }
    else
    {
        int val = _wtoi(gs.String());
        if (val < 10 || val > 1000)
        {
            RhinoApp().Print(L"Grid size must be between 10 and 1000. Using default value of 100.\n");
            gridSize = 100;
        }
        else
        {
            gridSize = val;
        }
    }


    double minDistance = DBL_MAX;
    double maxDistance = 0.0;
    double totalDistance = 0.0;
    int numSamples = 0;

    ON_3dPoint minPoint1, minPoint2;
    ON_3dPoint maxPoint1, maxPoint2;
    double minU1 = 0.0, minV1 = 0.0, minU2 = 0.0, minV2 = 0.0;
    double maxU1 = 0.0, maxV1 = 0.0, maxU2 = 0.0, maxV2 = 0.0;

    // Iterate over the grid points on surface1
    for (int i = 0; i < gridSize; ++i)
    {
        double u = surface1->Domain(0).ParameterAt((double)i / (gridSize - 1));

        for (int j = 0; j < gridSize; ++j)
        {
            double v = surface1->Domain(1).ParameterAt((double)j / (gridSize - 1));

            // Evaluate the point on surface1
            ON_3dPoint point1;
            surface1->EvPoint(u, v, point1);

            // Find the closest point on surface2
            double u2, v2;
            if (surface2->GetClosestPoint(point1, &u2, &v2))
            {
                ON_3dPoint point2;
                surface2->EvPoint(u2, v2, point2);

                // Compute the distance between the points
                double distance = point1.DistanceTo(point2);

                // Update min, max, and total distance
                if (distance < minDistance)
                {
                    minDistance = distance;
                    minPoint1 = point1;
                    minPoint2 = point2;
                    minU1 = u;
                    minV1 = v;
                    minU2 = u2;
                    minV2 = v2;
                }
                if (distance > maxDistance)
                {
                    maxDistance = distance;
                    maxPoint1 = point1;
                    maxPoint2 = point2;
                    maxU1 = u;
                    maxV1 = v;
                    maxU2 = u2;
                    maxV2 = v2;
                }
                totalDistance += distance;
                numSamples++;
            }
        }
    }

    double averageDistance = totalDistance / numSamples;

    // Draw lines for min and max distance
    CRhinoObjectAttributes min_attributes;
    min_attributes.m_color = ON_Color(0, 255, 0); // Set color to green
    min_attributes.SetColorSource(ON::color_from_object);
    min_attributes.m_plot_color = min_attributes.m_color;
    min_attributes.SetPlotColorSource(ON::plot_color_from_object);
    //min_attributes.SetPlotWeight(0.35); // Set line thickness in millimeters
    min_attributes.SetPlotWeightSource(ON::plot_weight_from_object);

    // Create attributes for maximum distance line
    CRhinoObjectAttributes max_attributes;
    max_attributes.m_color = ON_Color(255, 0, 0); // Set color to red
    max_attributes.SetColorSource(ON::color_from_object);
    max_attributes.m_plot_color = max_attributes.m_color;
    max_attributes.SetPlotColorSource(ON::plot_color_from_object);
    //max_attributes.SetPlotWeight(0.35); // Set line thickness in millimeters
    max_attributes.SetPlotWeightSource(ON::plot_weight_from_object);

    // Draw the minimum distance line with specified attributes
    context.m_doc.AddCurveObject(ON_LineCurve(minPoint1, minPoint2), &min_attributes);

    // Draw the maximum distance line with specified attributes
    context.m_doc.AddCurveObject(ON_LineCurve(maxPoint1, maxPoint2), &max_attributes);

    // Redraw views to display new lines with updated properties
    context.m_doc.Redraw();



   // Print the coordinates of the points
   //RhinoApp().Print(L"minPoint1: (%.6f, %.6f, %.6f)\n", minPoint1.x, minPoint1.y, minPoint1.z);
   //RhinoApp().Print(L"minPoint2: (%.6f, %.6f, %.6f)\n", minPoint2.x, minPoint2.y, minPoint2.z);
   //RhinoApp().Print(L"maxPoint1: (%.6f, %.6f, %.6f)\n", maxPoint1.x, maxPoint1.y, maxPoint1.z);
   //RhinoApp().Print(L"maxPoint2: (%.6f, %.6f, %.6f)\n", maxPoint2.x, maxPoint2.y, maxPoint2.z);
  
    // Print the min and max u, v parameter values
    RhinoApp().Print(L"Min u1: %.6f, Min v1: %.6f\n", minU1, minV1);
    RhinoApp().Print(L"Min u2: %.6f, Min v2: %.6f\n", minU2, minV2);
    RhinoApp().Print(L"Max u1: %.6f, Max v1: %.6f\n", maxU1, maxV1);
    RhinoApp().Print(L"Max u2: %.6f, Max v2: %.6f\n", maxU2, maxV2);

    // Print the results
    RhinoApp().Print(L"Min Distance: %.6f\n", minDistance);
    RhinoApp().Print(L"Max Distance: %.6f\n", maxDistance);
    RhinoApp().Print(L"Average Distance: %.6f\n", averageDistance);

    context.m_doc.Redraw();

    return CRhinoCommand::success;
}
#pragma endregion

//
// END GTest command
//

 