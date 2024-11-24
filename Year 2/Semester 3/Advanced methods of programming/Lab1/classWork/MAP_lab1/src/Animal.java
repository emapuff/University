
public class Animal {
    private int age;
    private String name;
    public Animal(){} //constructor default
    public Animal(int age, String name) {
        this.age = age;
        this.name = name;
    }
    public int getAge() {
        return age;
    }
    public void setAge(int age) {
        this.age = age;
    }

    public void showDetails(){
        System.out.println(this.age+" "+this.name);
    }
}
