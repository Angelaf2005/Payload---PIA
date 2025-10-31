# Tarea 5 — Primer avance PIA — "Equipo Trueno"

## 🧠 Resumen del proyecto
Desarrollar un payload educativo en C++ que simule una petición de red `GET /status` controlada a un servidor local como opcion default, sin persistencia ni exfiltración, para fines educativos en entornos seguros.

## 📌 Alcance y límites
**Permitido:**
- Compilación y ejecución en VM aisladas
- Petición GET a servidor controlado
- Registro de salida en consola
- Análisis estático y dinámico en laboratorio

**Prohibido:**
- Persistencia en el sistema
- Ejecución de comandos remotos
- Exfiltración de datos
- Interacción con redes reales o públicas

## 🗓️ Plan de trabajo por fases
- **Fase 1 (Tarea 5):** Definición del proyecto, estructura del repositorio, medidas éticas — *31 oct 2025*
- **Fase 2 (Tarea 6):** Implementación del cliente C++ y pruebas básicas — *7 nov 2025*
- **Fase 3:** Desarrollo del servidor de prueba y análisis inicial — *14 nov 2025*
- **Fase 4 (Entrega Final):** Integración completa, análisis avanzado y entrega final — *20 nov 2025*

## 👥 Distribución de tareas

### 🔹 Fase 1 — Inicio del proyecto (Tarea 5)
- **Integrante 1**: Coordinación general y documentación ética (`README.md`, `ETHICS.md`, `TEAM_PLAN.md`)
- **Integrante 2**: Estructura del repositorio y configuración inicial (`/src`, `/docs`, `/bin`)
- **Integrante 3**: Redacción del plan de trabajo y distribución de tareas
- **Integrante 4**: Validación de medidas éticas y preparación del commit/tag inicial

### 🔹 Fase 2 — Implementación técnica (Tarea 6)
- **Integrante 1**: Desarrollo del cliente C++ mínimo funcional
- **Integrante 2**: Diseño y pruebas del servidor de control (Python)
- **Integrante 3**: Pruebas en VM aislada y documentación en `tests.md`
- **Integrante 4**: Instrucciones de compilación y generación de binarios

### 🔹 Fase 3 — Integración y análisis (Tercer avance)
- **Integrante 1**: Análisis estático con Ghidra y exportación de resultados
- **Integrante 2**: Análisis dinámico en sandbox y captura de logs
- **Integrante 3**: Organización de evidencias multimedia (`/evidence`) y documentación técnica (`report_draft.md`)
- **Integrante 4**: Actualización de `CHANGELOG.md` y validación de cumplimiento ético

### 🔹 Fase 4 — Entrega final del proyecto (20 nov 2025)
- **Integrante 1**: Redacción del reporte técnico final (`docs/report_final.pdf`), integración de anexos y referencias con evidencias
- **Integrante 2**: Consolidación de binarios (`/bin`), validación de compilación, actualización de `README.md`
- **Integrante 3**: Revisión y documentación del entorno técnico (`METADATA.md`), checklist de entrega (`DELIVERY_CHECKLIST.md`), validación de estructura del repositorio
- **Integrante 4**: Revisión final de `ETHICS.md` y `CHANGELOG.md`, organización de evidencias multimedia (`/evidence`)


## 🔐 Medidas éticas y de seguridad

- Todas las pruebas se realizarán exclusivamente en máquinas virtuales configuradas en modo aislado (host-only o internal-only), sin acceso a redes externas.
- Se utilizarán snapshots antes de cada sesión de prueba para garantizar entornos reproducibles y revertibles.
- En caso de fallos o comportamientos inesperados, se aplicará restauración automática desde el snapshot correspondiente.
- El payload no incluye mecanismos de persistencia, ejecución remota ni exfiltración de datos.
- No se almacenarán credenciales, datos sensibles ni información personal.

## 🏷️ TAG inicial
Tag: `tarea5-inicio`