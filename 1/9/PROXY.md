```
classDiagram
Client ..> ISubject: "use"
Subject ..|> ISubject
SubjectProxy ..|> ISubject
SubjectProxy --> Subject

    class Client {

    }

    class ISubject {

    }

    class Subject {

    }

    class SubjectProxy {

    }
```