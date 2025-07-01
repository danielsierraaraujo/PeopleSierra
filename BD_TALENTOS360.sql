CREATE DATABASE DB_TALENTOS360
GO
USE DB_TALENTOS360
GO
CREATE TABLE tb_Estudiante
(
IdEstudiante INT IDENTITY (1,1) NOT NULL,
NombreCompleto VARCHAR(30) NOT NULL,
FechaDeNacimiento DATE NOT NULL,
Categoria VARCHAR(30) NOT NULL,
Correo VARCHAR(30) NOT NULL,
Telefono VARCHAR(30) NOT NULL
CONSTRAINT PK_tb_Estudiante PRIMARY KEY (IdEstudiante),
CONSTRAINT CH_tb_Estudiante_Categoria CHECK (Categoria IN('Nuevo','Regular','Egresado')), 
CONSTRAINT UK_Correo_Estudiante UNIQUE (Correo),
CONSTRAINT CH_Estudiante_Telefono CHECK (LEN(Telefono)=10)
)
CREATE TABLE tb_Curso
(
IdCurso INT IDENTITY (1,1) NOT NULL,
Duraci�n TIME NOT NULL,
Nombre VARCHAR (30) NOT NULL,
AreaTematica VARCHAR(30) NOT NULL,
Descripcion VARCHAR(30) NOT NULL,
Nivel VARCHAR(30) NOT NULL
CONSTRAINT PK_tb_Curso PRIMARY KEY (IdCurso),
CONSTRAINT CH_tb_Curso_Nivel CHECK (Nivel IN('Basico','Intermedio','Avanzado')), 
)
CREATE TABLE tb_Instructor
(
IdInstructor INT IDENTITY (1,1) NOT NULL,
NombreCompleto VARCHAR (50) NOT NULL,
Especialidad VARCHAR(30) NOT NULL,
A�osExperiencia INT NOT NULL,
Contrato VARCHAR(30) NOT NULL
CONSTRAINT PK_tb_Instructor PRIMARY KEY (IdInstructor),
CONSTRAINT CH_tb_Instructor_Contrato CHECK (Contrato IN('Tiempo Completo','Medio Tiempo','Por horas')), 
CONSTRAINT CH_Instructor_A�osExperiencia CHECK (A�osExperiencia>=0)
)
CREATE TABLE tb_Edici�n
(
IdEdici�n INT IDENTITY (1,1) NOT NULL,
Modalidad VARCHAR (50) NOT NULL,
FechaInicio DATE NOT NULL,
FechaFinal DATE NOT NULL,
IdCurso INT NOT NULL
CONSTRAINT PK_tb_Edici�n PRIMARY KEY (IdEdici�n),
CONSTRAINT CH_tb_Edici�n_Modalidad CHECK (Modalidad IN('Presencial','Virtual','Hibrida')), 
CONSTRAINT FK_tb_Edici�n_tb_Curso FOREIGN KEY (IdCurso) References tb_Curso(IdCurso)
)

CREATE TABLE tb_Evaluacion
(
IdEvaluaci�n INT IDENTITY (1,1) NOT NULL,
Tipo VARCHAR (30) NOT NULL,
Descripcion VARCHAR (30) NOT NULL,
PuntajeMaximo DECIMAL(10,2)NOT NULL,
Fecha DATETIME NOT NULL,
IdEdici�n INT NOT NULL,
CONSTRAINT PK_tb_Evaluaci�n PRIMARY KEY (IdEvaluaci�n),
CONSTRAINT FK_tb_Evaluaci�n_tb_Edici�n FOREIGN KEY (IdEdici�n) References tb_Edici�n(IdEdici�n)
)
CREATE TABLE tb_Encuesta
(
IdEncuesta INT IDENTITY (1,1) NOT NULL,
Comentarios VARCHAR (100) NOT NULL,
Fecha Date  NOT NULL,
Calificaci�n DECIMAL(10,2)NOT NULL,
IdEdici�n INT NOT NULL,
IdEstudiante INT NOT NULL,
CONSTRAINT PK_tb_Encuesta PRIMARY KEY (IdEncuesta),
CONSTRAINT FK_tb_Encuesta_tb_Edici�n FOREIGN KEY (IdEdici�n) References tb_Edici�n(IdEdici�n),
CONSTRAINT FK_tb_Encuesta_tb_Estudiante FOREIGN KEY (IdEstudiante) References tb_Estudiante(IdEstudiante)
)
CREATE TABLE tb_Inscripcion
(
IdInscripcion INT IDENTITY (1,1) NOT NULL,
Estado VARCHAR (100) NOT NULL,
FechadeInscripcion Date  NOT NULL,
IdEdici�n INT NOT NULL,
IdEstudiante INT NOT NULL,
CONSTRAINT PK_tb_Inscripcion PRIMARY KEY (IdInscripcion),
CONSTRAINT FK_tb_Inscripcion_tb_Edici�n FOREIGN KEY (IdEdici�n) References tb_Edici�n(IdEdici�n),
CONSTRAINT FK_tb_Inscripcion_tb_Estudiante FOREIGN KEY (IdEstudiante) References tb_Estudiante(IdEstudiante),
CONSTRAINT CH_tb_Inscripcion_Estado CHECK (Estado IN('Activo','Retirado','Finalizado')), 
)
CREATE TABLE tb_Entrega
(
IdEntrega INT IDENTITY (1,1) NOT NULL,
IdEstudiante INT NOT NULL,
IdEvaluaci�n INT NOT NULL,
Calificaci�nFinal DECIMAL(10,2)NOT NULL,
CONSTRAINT PK_tb_Entrega PRIMARY KEY (IdEntrega),
CONSTRAINT FK_tb_Entrega_tb_Evaluaci�n FOREIGN KEY (IdEvaluaci�n) References tb_Evaluacion(IdEvaluaci�n),
CONSTRAINT FK_tb_Entrega_tb_Estudiante FOREIGN KEY (IdEstudiante) References tb_Estudiante(IdEstudiante),
)

CREATE TABLE tb_Instructoredicion
(
IdInstructoredicion INT IDENTITY (1,1) NOT NULL,
IdInstructor INT NOT NULL,
IdEdici�n INT NOT NULL,
CONSTRAINT PK_tb_Instructoredicion PRIMARY KEY (IdInstructoredicion),
CONSTRAINT FK_tb_Instructoredicion_tb_Instructor FOREIGN KEY (IdInstructor) References tb_Instructor(IdInstructor),
CONSTRAINT FK_tb_Instructoredicion_tb_Edicion FOREIGN KEY (IdEdici�n) References tb_Edici�n(IdEdici�n),
)

