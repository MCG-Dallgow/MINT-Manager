#pragma once

inline const QString APPLICATION_NAME = "MINT-Verwaltung";
inline const QString APPLICATION_VERSION = "0.1.0";
inline const QStringList MINT_SUBJECTS = {"Biologie", "Chemie", "Informatik", "Mathematik", "Physik", "Technik"};

enum class ScientificWork
{
    NOTHING,
    FACHWISSENSCHAFTLICHE_ARBEIT,
    WISSENSCHAFTSPROPAEDEUTISCHES_FACH,
    JUGEND_FORSCHT,
    BESONDERE_LERNLEISTUNG,
    SONSTIGES
};

