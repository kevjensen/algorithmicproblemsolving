//
// Created by kev_j on 5/9/2020.
//

#include "Botan.h"


bool botan_256_hash(std::string &input, std::string &output) {
    std::string hash_value;
    try {
        std::unique_ptr<Botan::HashFunction> hash1(Botan::HashFunction::create_or_throw("SHA-256"));

        //update hash computations with data
        hash1->update(input);

        hash_value = Botan::hex_encode(hash1->final());
    } catch (Botan::Lookup_Error &e) {
        std::cout << "Caught: " << e.what() << "\n";
    }
    return hash_value == output;
}

bool botan_256_hash_iteration(std::string &input, const int &iterations, std::string &output) {
    std::string hash_value;
    std::unique_ptr<Botan::HashFunction> hash1(Botan::HashFunction::create("SHA-256"));
    for (int i = 0; i < iterations; ++i) {
        //update hash computations with data
        hash1->update(input);
        hash_value = Botan::hex_encode(hash1->final());
    }
    return hash_value == output;
}

bool pbkdf2_hash_match(const size_t &iterations,
                       const std::vector<uint8_t> &salt,
                       const std::string &passphrase,
                       const std::vector<uint8_t> &output) {

    auto pwdhash_fam = Botan::PasswordHashFamily::create("PBKDF2(HMAC(SHA-256))");
    auto pwdhash = pwdhash_fam->from_params(iterations);
    std::vector<uint8_t> pwdhash_derived(output.size());


    pwdhash->derive_key(pwdhash_derived.data(), pwdhash_derived.size(), passphrase.c_str(),
                        passphrase.size(), salt.data(), salt.size());

    return pwdhash_derived == output;
}

// bcrypt
bool bcrypt_check(const std::string &pass, const std::string &hash) {
    return Botan::check_bcrypt(pass, hash);
}

bool scrypt_hash(const std::string &passphrase, const std::vector<uint8_t> &salt,
                 const std::vector<uint8_t> &output, const size_t &N, const size_t &R,
                 const size_t &P) {

    auto pwdhash_fam = Botan::PasswordHashFamily::create("Scrypt");

    if(!pwdhash_fam)
    {
        std::cout << "Scrypt is missing PasswordHashFamily";
        return false;
    }

    auto pwdhash = pwdhash_fam->from_params(N, R, P);

    std::vector<uint8_t> pwdhash_derived(output.size());

    pwdhash->derive_key(pwdhash_derived.data(), pwdhash_derived.size(),
                        passphrase.c_str(), passphrase.size(), salt.data(), salt.size());

    return pwdhash_derived == output;
}

// Argon2id
bool argon2_check(const char *pass, size_t password_len, const std::string &hash) {
    return Botan::argon2_check_pwhash(pass, password_len, hash);

}