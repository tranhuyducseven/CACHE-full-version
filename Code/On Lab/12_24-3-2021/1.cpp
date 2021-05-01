

void Polynomial::insertTerm(const Term& term) {
    // STUDENT ANSWER
    if (term.coeff == 0.0) return;
    if (terms->empty()) terms->add(term);
    else {
        int i = 0;
        Term t = terms->get(i);
        while (term.exp < t.exp) 
        {
            i++;
            if (i == terms->size()) {
                terms->add(term);
                return;
            }
            else t = terms->get(i);
        }
        if (term.exp == t.exp) {
            t.coeff += term.coeff;
            if (t.coeff == 0) terms->removeAt(i);
            else terms->set(i, t);
        }
        else terms->add(i, term);
    }
}

void Polynomial::insertTerm(double coeff, int exp) {
    // STUDENT ANSWER
    Term t = Term(coeff, exp);
    insertTerm(t);
}