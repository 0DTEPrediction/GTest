// cmdGTest.cpp : command file
//

#include "stdafx.h"
#include "GTestPlugIn.h"
#include "RhinoSdkCommand.h"
#include <iostream>  // This header includes std::cerr and std::endl

////////////////////////////////////////////////////////////////
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
        //{ // {12345678-1234-5678-1234-567812345678}
        //0x12345678, 0x1234, 0x5678, { 0x12, 0x34, 0x56, 0x78, 0x12, 0x34, 0x56, 0x78 } };
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
}
#pragma endregion


//
// END GTest command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
 