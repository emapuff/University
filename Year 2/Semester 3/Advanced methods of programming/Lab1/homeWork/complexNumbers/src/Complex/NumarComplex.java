package Complex;

public class NumarComplex {
    private float re;
    private float im;

    public NumarComplex(float re, float im) {
        this.re = re;
        this.im = im;
    }

    public NumarComplex adunare(NumarComplex other){
        return new NumarComplex(this.re + other.re, this.im + other.im);
    }

    public NumarComplex scaere(NumarComplex other){
        return new NumarComplex(this.re - other.re, this.im - other.im);
    }

    public NumarComplex inmultire(NumarComplex other){
        float re = this.re * other.re - this.im * other.im;
        float im = this.re * other.im + this.im * other.re;
        return new NumarComplex(re, im);
    }

    public NumarComplex impartire(NumarComplex other) {
        float re = (this.re * other.re + this.im * other.im) / (other.re * other.re + other.im * other.im);
        float im = (other.re * this.im - this.re * other.re / (other.re * other.re + other.im * other.im));
        return new NumarComplex(re, im);
    }

    @Override
    public String toString() {
        return re + " "+ im + "*i";
    }
}
