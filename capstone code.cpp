#include "jit_compiler.h" 
#include <iostream> 
#include <cstring> 
JITCompiler::JITCompiler() { 
    memset(registers, 0, sizeof(registers)); 
} 
void JITCompiler::addInstruction(Operation op, int operand1, int operand2, 
int result) { 
    instructions.push_back({op, operand1, operand2, result}); 
} 
void JITCompiler::translateToMachineCode() { 
    for (const auto& instr : instructions) { 
        switch (instr.op) { 
        case Operation::ADD: 
            machineCode.push_back(0x01); // Opcode for ADD 
            machineCode.push_back(instr.operand1); 
            machineCode.push_back(instr.operand2); 
            machineCode.push_back(instr.result); 
            break; 
        case Operation::SUB: 
            machineCode.push_back(0x02); // Opcode for SUB 
            machineCode.push_back(instr.operand1); 
            machineCode.push_back(instr.operand2); 
            machineCode.push_back(instr.result); 
            break; 
        case Operation::HALT: 
            machineCode.push_back(0xFF); // Opcode for HALT 
            break; 
        default: 
            std::cerr << "Unsupported operation\n"; 
        } 
    } 
} 
void JITCompiler::compile() { 
    translateToMachineCode(); 
} 
int JITCompiler::execute() { 
    size_t pc = 0; // Program counter 
    while (pc < machineCode.size()) { 
        uint8_t opcode = machineCode[pc]; 
        switch (opcode) { 
        case 0x01: // ADD 
            registers[machineCode[pc + 3]] = registers[machineCode[pc + 1]] + 
registers[machineCode[pc + 2]]; 
            pc += 4; 
            break; 
        case 0x02: // SUB 
            registers[machineCode[pc + 3]] = registers[machineCode[pc + 1]] - 
registers[machineCode[pc + 2]]; 
            pc += 4; 
            break; 
        case 0xFF: // HALT 
            return registers[0]; 
        default: 
            std::cerr << "Invalid opcode\n"; 
            return -1; 
        } 
    } 
    return registers[0]; 
} 
