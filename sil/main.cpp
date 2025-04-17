// vcu_module.cpp (or your chosen filename)

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // May be needed if any members use std containers, good practice to include

// Include the necessary C++ headers for the VCU model and its components
// Adjust paths as needed for your build system
#include "../inc/VcuModel.h"
#include "../inc/VcuParameters.h"  // Assuming this contains definitions if not fully in VcuModel.h
#include "../inc/blocks/AppsProcessor.h"
#include "../inc/blocks/BrakeLight.h"
#include "../inc/blocks/Cooling.h"
#include "../inc/blocks/Stompp.h"
#include "../inc/blocks/TorqueMap.h"

namespace py = pybind11;

// --- Forward declare STOMPPStatus if needed (or include the defining header)
// --- Example: If STOMPP_OK comes from an enum like this in Stompp.h: enum
// STOMPPStatus { STOMPP_OK, STOMPP_ERROR1, STOMPP_ERROR2 }; You might need to
// bind the enum too. Assuming Stompp.h defines it.

// --- Binding Code ---
PYBIND11_MODULE(vcu, m) {  // Renamed 'module_handle' to 'm' for convention
    m.doc() = "Python bindings for the VCU Model C++ library";

    // --- Bind Enums (Example for STOMPPStatus if it exists) ---
    // Check Stompp.h for the actual definition
    /* Example:
    py::enum_<STOMPPStatus>(m, "STOMPPStatus")
        .value("OK", STOMPP_OK)
        // Add other enum values if they exist
        .value("ERROR1", STOMPP_ERROR1)
        .export_values(); // Makes enum values accessible directly (e.g.,
    vcu.STOMPPStatus.OK)
    */
    // Assuming STOMPP_OK is just an int/define for now based on the C code.
    // If STOMPPOutputs::output is an enum, bind the enum and use it below.

    // --- Bind Nested Structs (Inputs) ---
    py::class_<APPSInputs>(m, "APPSInputs")
        .def(py::init<>())  // Default constructor
        .def_readwrite("sensor1", &APPSInputs::sensor1)
        .def_readwrite("sensor2", &APPSInputs::sensor2)
        // Add other APPSInputs members if they exist
        .doc() = "Inputs for the APPS Processor block";

    py::class_<STOMPPInputs>(m, "STOMPPInputs")
        .def(py::init<>())
        .def_readwrite("apps_percent", &STOMPPInputs::apps_percent)
        .def_readwrite("brake_active", &STOMPPInputs::brake_active)
        // Add other STOMPPInputs members if they exist
        .doc() = "Inputs for the STOMPP block";

    py::class_<TorqueMapInputs>(m, "TorqueMapInputs")
        .def(py::init<>())
        .def_readwrite("apps", &TorqueMapInputs::apps)
        .def_readwrite("rpm", &TorqueMapInputs::rpm)
        // Add other TorqueMapInputs members if they exist
        .doc() = "Inputs for the Torque Map block";

    py::class_<CoolingInputs>(m, "CoolingInputs")
        .def(py::init<>())
        .def_readwrite("motor_rpm", &CoolingInputs::motor_rpm)
        .def_readwrite("motor_temp", &CoolingInputs::motor_temp)
        .def_readwrite("battery_temp", &CoolingInputs::battery_temp)
        // Add other CoolingInputs members if they exist
        .doc() = "Inputs for the Cooling block";

    py::class_<BrakeLightInputs>(m, "BrakeLightInputs")
        .def(py::init<>())
        .def_readwrite("brake_pressure", &BrakeLightInputs::brake_pressure)
        // Add other BrakeLightInputs members if they exist
        .doc() = "Inputs for the Brake Light block";

    // --- Bind Nested Structs (Outputs) ---
    py::class_<APPSOutputs>(m, "APPSOutputs")
        .def(py::init<>())
        .def_readwrite("pedalPercent", &APPSOutputs::pedalPercent)
        // Add other APPSOutputs members if they exist
        .doc() = "Outputs for the APPS Processor block";

    py::class_<STOMPPOutputs>(m, "STOMPPOutputs")
        .def(py::init<>())
        // Assuming 'output' is an int or a type convertible from int.
        // If it's an enum (like STOMPPStatus), ensure the enum is bound (see
        // above).
        .def_readwrite("output", &STOMPPOutputs::output)
        // Add other STOMPPOutputs members if they exist
        .doc() = "Outputs for the STOMPP block";

    py::class_<TorqueMapOutputs>(m, "TorqueMapOutputs")
        .def(py::init<>())
        .def_readwrite("torqueRequest", &TorqueMapOutputs::torqueRequest)
        // Add other TorqueMapOutputs members if they exist
        .doc() = "Outputs for the Torque Map block";

    py::class_<CoolingOutputs>(m, "CoolingOutputs")
        .def(py::init<>())
        .def_readwrite("motor_fan_speed", &CoolingOutputs::motor_fan_speed)
        .def_readwrite("battery_fan_speed", &CoolingOutputs::battery_fan_speed)
        // Add other CoolingOutputs members if they exist
        .doc() = "Outputs for the Cooling block";

    py::class_<BrakeLightOutputs>(m, "BrakeLightOutputs")
        .def(py::init<>())
        .def_readwrite("light_active", &BrakeLightOutputs::light_active)
        // Add other BrakeLightOutputs members if they exist
        .doc() = "Outputs for the Brake Light block";

    // --- Bind Nested Structs (Parameters) ---
    py::class_<APPSParameters>(m, "APPSParameters")
        .def(py::init<>())
        // Add all APPSParameters members using def_readwrite
        // .def_readwrite("param1", &APPSParameters::param1)
        .doc() = "Parameters for the APPS Processor block";

    py::class_<STOMPPParameters>(m, "STOMPPParameters")
        .def(py::init<>())
        // Add all STOMPPParameters members using def_readwrite
        // .def_readwrite("param1", &STOMPPParameters::param1)
        .doc() = "Parameters for the STOMPP block";

    py::class_<TorqueMapParameters>(m, "TorqueMapParameters")
        .def(py::init<>())
        // Add all TorqueMapParameters members using def_readwrite
        // .def_readwrite("param1", &TorqueMapParameters::param1)
        .doc() = "Parameters for the Torque Map block";

    py::class_<CoolingParameters>(m, "CoolingParameters")
        .def(py::init<>())
        // Add all CoolingParameters members using def_readwrite
        // .def_readwrite("param1", &CoolingParameters::param1)
        .doc() = "Parameters for the Cooling block";

    py::class_<BrakeLightParameters>(m, "BrakeLightParameters")
        .def(py::init<>())
        // Add all BrakeLightParameters members using def_readwrite
        // .def_readwrite("param1", &BrakeLightParameters::param1)
        .doc() = "Parameters for the Brake Light block";

    // --- Bind Top-Level Structs ---
    py::class_<VCUModelInputs>(m, "VCUModelInputs")
        .def(py::init<>())
        .def_readwrite("apps", &VCUModelInputs::apps)
        .def_readwrite("stompp", &VCUModelInputs::stompp)
        .def_readwrite("torque", &VCUModelInputs::torque)
        .def_readwrite("cooling", &VCUModelInputs::cooling)
        .def_readwrite("brake_light", &VCUModelInputs::brake_light)
        .def_readwrite("drive_switch_enabled",
                       &VCUModelInputs::drive_switch_enabled)
        .doc() = "Aggregate inputs for the VCU Model";

    py::class_<VCUModelOutputs>(m, "VCUModelOutputs")
        .def(py::init<>())
        .def_readwrite("apps", &VCUModelOutputs::apps)
        .def_readwrite("stompp", &VCUModelOutputs::stompp)
        .def_readwrite("torque", &VCUModelOutputs::torque)
        .def_readwrite("cooling", &VCUModelOutputs::cooling)
        .def_readwrite("brake_light", &VCUModelOutputs::brake_light)
        .doc() = "Aggregate outputs from the VCU Model";

    py::class_<VCUModelParameters>(m, "VCUModelParameters")
        .def(py::init<>())
        .def_readwrite("apps", &VCUModelParameters::apps)
        .def_readwrite("stompp", &VCUModelParameters::stompp)
        .def_readwrite("torque", &VCUModelParameters::torque)
        .def_readwrite("cooling", &VCUModelParameters::cooling)
        .def_readwrite("brake_light", &VCUModelParameters::brake_light)
        .doc() = "Aggregate parameters for the VCU Model";

    // --- Bind Functions ---
    m.def("evaluate", &VCUModel_evaluate,
          "Evaluates the VCU model based on inputs and deltaTime, updating "
          "outputs.",
          py::arg("inputs"), py::arg("outputs"), py::arg("deltaTime"));

    m.def("set_parameters", &VCUModel_set_parameters,
          "Sets the parameters for the entire VCU model.",
          py::arg("parameters"));

    // --- Keep or remove benchmark_lol ---
    // Example C++ function (from your original code)
    auto benchmark_lol = []() {
        // Made loop smaller for quicker testing
        for (long long i = 0; i < 1000000; i++) {
            volatile long long k = i;  // Prevent optimization
        }
        return 1;
    };
    m.def("benchmark_lol", benchmark_lol, "A simple benchmark function.");

}  // end PYBIND11_MODULE