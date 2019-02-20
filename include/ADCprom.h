int lecturaADCn(int n){
      long suma=0;
      for(i=1; i<=n;i++){ //se puede modificar el "8" por una n.
        suma=suma+analogRead(A0);
      }
      return(suma/n);
}
