# 🔐 PassSmith

**A smart, human-targeted password wordlist generator for penetration testing and security research.**

Unlike traditional brute-force tools, PassSmith generates intelligent wordlists based on personal information and common password patterns that humans actually use.

```
░█████████                                     ░██████                   ░██   ░██    ░██        
░██     ░██                                   ░██   ░██                        ░██    ░██        
░██     ░██  ░██████    ░███████   ░███████  ░██         ░█████████████  ░██░████████ ░████████  
░█████████        ░██  ░██        ░██         ░████████  ░██   ░██   ░██ ░██   ░██    ░██    ░██ 
░██          ░███████   ░███████   ░███████          ░██ ░██   ░██   ░██ ░██   ░██    ░██    ░██ 
░██         ░██   ░██         ░██        ░██  ░██   ░██  ░██   ░██   ░██ ░██   ░██    ░██    ░██  
░██          ░█████░██  ░███████   ░███████    ░██████   ░██   ░██   ░██ ░██    ░████ ░██    ░██ 
```

## ✨ Features

- **Human-Focused**: Generates passwords based on real human behavior and patterns
- **Smart Combinations**: Creates intelligent word combinations with separators
- **Multiple Transformations**: Uppercase, lowercase, reverse, leet speak variations
- **Common Patterns**: Includes typical password endings (123, !, @, years, etc.)
- **CLI Friendly**: Full command-line argument support for scripting
- **Fast & Lightweight**: Written in C for maximum performance
- **Cross-Platform**: Works on Linux, macOS, and Windows

## 🚀 Quick Start

### Compilation
```bash
gcc -o passsmith passsmith.c
```

### Basic Usage
```bash
# Interactive mode
./passsmith

# Command line keywords
./passsmith john 1990 soccer

# Specify output file
./passsmith -o custom.txt alice 1985 cat

# Quiet mode for scripting
./passsmith -q -o wordlist.txt admin 2024
```

## 📖 Usage Examples

### Target Information Gathering
PassSmith excels when you have target information like:
- **Names**: john, alice, smith
- **Years**: birth year, graduation, employment
- **Interests**: soccer, guitar, travel
- **Pets**: max, bella, charlie
- **Companies**: tesla, google, microsoft

### Example Scenarios

**Social Engineering Assessment:**
```bash
./passsmith -o client_wordlist.txt johnson 1987 marketing tesla
```

**Corporate Penetration Test:**
```bash
./passsmith -w companyname -w 2024 -w admin -o corp_passwords.txt
```

**Personal Target:**
```bash
./passsmith sarah 1992 yoga brooklyn -o personal.txt
```

## 🛠️ Command Line Options

| Option | Description | Example |
|--------|-------------|---------|
| `-o FILE` | Specify output file | `-o mylist.txt` |
| `-q` | Quiet mode (minimal output) | `-q` |
| `-h` | Show help message | `-h` |
| `-n` | No banner | `-n` |
| `-w WORD` | Add keyword (repeatable) | `-w admin -w 2024` |

## 🧠 How It Works

PassSmith generates passwords using multiple strategies:

### 1. **Base Transformations**
- Original word: `john`
- Uppercase: `JOHN`  
- Lowercase: `john`
- Reversed: `nhoj`
- Leet speak: `j0hn`

### 2. **Common Endings**
- `john123`, `john!`, `john@`, `john2024`

### 3. **Word Combinations**
- Two words: `john1990`, `john_soccer`, `john-admin`
- Three words: `john_soccer_1990`

### 4. **Pattern Variations**
- Different separators: `_`, `-`, `.`, `~`
- Mixed with endings: `john_1990!`, `admin-2024@`

## 📊 Output Examples

**Input:** `john`, `1990`, `soccer`

**Sample Generated Passwords:**
```
john
JOHN
nhoj  
j0hn
john123
john!
john1990
john_soccer
soccer1990!
john_soccer_1990
1990-john@
...and many more
```

## 🎯 Use Cases

- **Penetration Testing**: Generate targeted wordlists for password attacks
- **Security Research**: Study common password patterns
- **Red Team Operations**: Social engineering password lists
- **Security Awareness**: Demonstrate password predictability
- **Compliance Testing**: Test password policies

## ⚠️ Ethical Use Only

PassSmith is designed for legitimate security testing and research purposes only. Users must:

- Have explicit permission to test target systems
- Comply with applicable laws and regulations
- Use responsibly in authorized security assessments
- Respect privacy and confidentiality

## 🔧 Advanced Usage

### Scripting Integration
```bash
# Generate wordlist and pipe to hashcat
./passsmith -q -o /tmp/wordlist.txt target_info 2024
hashcat -m 1000 hashes.txt /tmp/wordlist.txt

# Batch processing
for target in $(cat targets.txt); do
    ./passsmith -q -o ${target}_wordlist.txt $target 2024 admin
done
```

### Performance Tips
- Use `-q` flag for better performance in scripts
- Limit input keywords to avoid exponential growth
- Consider using `-n` to skip banner in automated workflows

## 📈 Statistics

PassSmith typically generates:
- **3 keywords**: ~500-800 passwords
- **5 keywords**: ~1,500-2,500 passwords  
- **10 keywords**: ~5,000-10,000 passwords

*Numbers vary based on transformations and combinations*

## 🤝 Contributing

Contributions are welcome! Areas for improvement:
- Additional transformation algorithms
- More password patterns
- Performance optimizations
- Platform-specific enhancements

## 📜 License

This project is licensed under the GPL-3.0 License - see the LICENSE file for details.

## 🔗 Related Tools

- **Crunch**: Traditional charset-based password generation
- **CeWL**: Web crawler wordlist generator  
- **CUPP**: Common User Passwords Profiler
- **Hashcat**: Password recovery tool
- **John the Ripper**: Password cracking utility

---

*Remember: The strongest passwords are the ones humans don't create.*
