#ifndef COMPILER_IR_PRINTER_H
#define COMPILER_IR_PRINTER_H

#include "ir.h"


class IRPrinter {
public:
    static void print(const std::vector<std::shared_ptr<Instruction>>& ir, const std::string& filename) {
        std::ofstream outFile(filename);

        if (!outFile) {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return;
        }

        bool lastWasLabel = false;

        for (const auto& instr : ir) {
            if (auto basic = std::dynamic_pointer_cast<BasicInstruction>(instr)) {
                if (basic->opcode == "emit_asm") {
                    outFile << "\t" << basic->value << std::endl;
                } else {
                    outFile << "\t" << basic->opcode;
                    for (const auto& reg : basic->registers) {
                        outFile << " " << (reg->isVirtual ? "%" : "") << reg->name;
                    }
                    if (!basic->value.empty()) {
                        outFile << ", " << basic->value;
                    }
                    outFile << std::endl;
                }
                lastWasLabel = false;
            } else if (auto branch = std::dynamic_pointer_cast<BranchInstruction>(instr)) {
                outFile << "\t" << branch->opcode << " " << branch->label << std::endl;
                lastWasLabel = false;
            } else if (auto label = std::dynamic_pointer_cast<Label>(instr)) {
                if (label->funcDecl && !lastWasLabel) {
                    outFile << std::endl;
                }
                outFile << label->label << ":" << std::endl;
                lastWasLabel = true;
            } else if (auto global = std::dynamic_pointer_cast<GlobalVariable>(instr)) {
                outFile << "\t" << global->directive << " " << global->label;
                if (!global->value.empty()) {
                    outFile << " " << global->value;
                }
                outFile << " (size: " << global->size << ")" << std::endl;
                lastWasLabel = false;
            } else {
                outFile << "\tUNKNOWN INSTRUCTION" << std::endl;
                lastWasLabel = false;
            }
        }

        outFile.close();
    }
};

#endif //COMPILER_IR_PRINTER_H
