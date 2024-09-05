Lesson 110: Create a blank C++ Pawn Class.

Lesson 111: Learn 'Components' in blueprints, each actor has a root component and root component can be replaced by other useful component, such as capsule component.
Compoent B can attach to Componet A. When A is moved or scaled, B will also changes.

Lesson 112: Learn 'Forward Declaration' such as: 
class UCapsuleComponent* CapsuleComp;
in .h file and with out #include relevant .h
Because we should include as little as possible in .h
We don't need the header to declare a pointer. 

Lesson 113: Constructed a Capsule Component, made it the root component.

Lesson 114: Create Components in C++ file, and attach them.

Lesson 115: Derived child blueprints from BasePawn class,but the component in it can't be edit and the propery is blank.

